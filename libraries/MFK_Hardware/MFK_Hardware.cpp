
#include "MFK_Hardware.h"


MFK_Hardware::MFK_Hardware() {
	this->signalController = SignalController::getInstance();

	ss = new SoftwareSerial(MFK_OUTDEV_RX, MFK_OUTDEV_TX);
	this->outDev = new MFK_OutputDevice(ss);

	this->inpDev = new MFK_InputDevice<MFK_InputDeviceClient>();

	if(MOTION_DETECT_ENABLED) {
		this->pirm = new PIRMotion<PIRMotionClient>(MFK_PIR_MOTION_PIN, 1);
	}
}

void MFK_Hardware::begin() {
	this->ss->begin(9600);
	this->constructSignalPatterns();
	this->signal(MFK_SIG_ERR);

	this->pirm->setReportInterval(PIR_REPORT_INTERVAL);
	this->pirm->setLagAfterMotion(PIR_LAG);
	this->pirm->registerClient(this);
}

void MFK_Hardware::update() {
	this->timer.update();
	this->inpDev->update();
	this->signalController->update();
	if(MOTION_DETECT_ENABLED)
		this->pirm->update();
}

void MFK_Hardware::invokePMotCallback(void) {
	if(SIGNALLING_ENABLED && this->inpDev->isIdle()) {
		Serial.println(F("motion detected"));
		this->signal(MFK_SIG_LOOKATME);
	}
}



void MFK_Hardware::constructSignalPatterns() {
	// MFK_SIG_LOOKATME = 0
	LedSignalSource *led0 = 
		new LedSignalSource(MFK_LED_PIN, 10, 2000);
	BuzzerSignalSource *buzz0 = 
		new BuzzerSignalSource(MFK_BUZZER_PIN, &timer, 10, 500);

	SignalPattern *pat = 
		new SignalPattern(MFK_SIG_LOOKATME, &this->timer, MFK_LookAtme_Run);
	pat->addSignalSource(led0);
	pat->addSignalSource(buzz0);
	this->signalController->setPattern(MFK_SIG_LOOKATME, pat);

	led0->addSigOffset(MFK_SIG_CORRECT, 5, 60);
	buzz0->addSigOffset(MFK_SIG_CORRECT, 10, 20);
	pat = new SignalPattern(MFK_SIG_CORRECT, &this->timer, MFK_SigCorrect_Run);
	pat->addSignalSource(led0);
	pat->addSignalSource(buzz0);
	this->signalController->setPattern(MFK_SIG_CORRECT, pat);

	led0->addSigOffset(MFK_SIG_WRONG, 5, 60);
	buzz0->addSigOffset(MFK_SIG_WRONG, 10, 20);
	pat = new SignalPattern(MFK_SIG_WRONG, &this->timer, MFK_SigWrong_Run);
	pat->addSignalSource(led0);
	pat->addSignalSource(buzz0);
	this->signalController->setPattern(MFK_SIG_WRONG, pat);

	led0->addSigOffset(MFK_SIG_ERR, 5, 60);
	buzz0->addSigOffset(MFK_SIG_ERR, 10, 20);
	pat = new SignalPattern(MFK_SIG_ERR, &this->timer, MFK_SigErr_Run);
	pat->addSignalSource(led0);
	pat->addSignalSource(buzz0);
	this->signalController->setPattern(MFK_SIG_ERR, pat);
}

void MFK_Hardware::signal(int signalIdx) {
	if(SIGNALLING_ENABLED) {
		this->signalController->start(signalIdx);
	} 
}



int MFK_Hardware::runSignal(int sigIdx) {
	/*
	Serial.print(F("runSignal: "));
	Serial.println(sigIdx);
	*/
	switch(sigIdx) {
		case MFK_SIG_LOOKATME:
			return this->timer.every(MFK_SIG_LOOKATME_PERIOD, \
					MFK_LookAtMe_Trigger, 3);
		case MFK_SIG_CORRECT:
			return this->timer.every(MFK_SIG_DEFAULT_PERIOD, \
					MFK_SigCorrect_Trigger, 1);
		case MFK_SIG_WRONG:
			return this->timer.every(MFK_SIG_DEFAULT_PERIOD, \
					MFK_SigWrong_Trigger, 2);
		case MFK_SIG_ERR:
			return this->timer.every(MFK_SIG_DEFAULT_PERIOD, \
					MFK_SigErr_Trigger, 3);
		default:
			break;
	}
	return -1;
}
void MFK_Hardware::triggerSignal(int sigIdx) {
	// const SignalPattern *p = this->signalController[sigIdx];
	SignalPattern *p = this->signalController->getPattern(sigIdx);
	if(p!=NULL) {
		/*
		Serial.print(F("sigIdx: "));
		Serial.println(sigIdx);
		*/
		p->trigger();
	}
	else {
		// Serial.println(F("no signal pattern"));
	}
}


// signal run & trigger functions
// I hate the following part
// maybe Timer should be changed
int MFK_LookAtme_Run() {
	return MFK_Hardware::getInstance()->runSignal(MFK_SIG_LOOKATME);
}
void MFK_LookAtMe_Trigger() {
	MFK_Hardware::getInstance()->triggerSignal(MFK_SIG_LOOKATME);
}

int  MFK_SigCorrect_Run() {
	return MFK_Hardware::getInstance()->runSignal(MFK_SIG_CORRECT);
}
void MFK_SigCorrect_Trigger() {
	MFK_Hardware::getInstance()->triggerSignal(MFK_SIG_CORRECT);
}

int  MFK_SigWrong_Run() {
	return MFK_Hardware::getInstance()->runSignal(MFK_SIG_WRONG);
}
void MFK_SigWrong_Trigger() {
	MFK_Hardware::getInstance()->triggerSignal(MFK_SIG_WRONG);
}

int  MFK_SigErr_Run() {
	return MFK_Hardware::getInstance()->runSignal(MFK_SIG_ERR);
}
void MFK_SigErr_Trigger() {
	MFK_Hardware::getInstance()->triggerSignal(MFK_SIG_ERR);
}
