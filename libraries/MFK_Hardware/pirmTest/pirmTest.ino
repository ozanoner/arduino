
#include <Arduino.h>
#include <SignalController.h>
#include <SignalPattern.h>
#include <LedSignalSource.h>
#include <BuzzerSignalSource.h>
#include <Timer.h>

#include <PIRMotion.h>
#include <PIRMotionClient.h>
#include <ClientOwner.h>

#define MFK_SIG_LOOKATME	0
#define MFK_SIG_CORRECT		1
#define MFK_SIG_WRONG		2
#define MFK_SIG_ERR			3

#define MFK_BUZZER_PIN 12
#define MFK_LED_PIN    13
#define MFK_PIRM_PIN    11


SignalController* signalController;
Timer timer;
PIRMotion<PIRMotionClient> pirm(MFK_PIRM_PIN, 1); 
PIRMotionClient cl;

void triggerSignal(int sigIdx) {
	SignalPattern *p = signalController->getPattern(sigIdx);
	if(p!=NULL) {
		Serial.print(sigIdx);
		p->trigger();
	}
}

int MFK_LookAtme_Run() {
	return timer.every(3000, MFK_LookAtMe_Trigger, 3);
}
void MFK_LookAtMe_Trigger() {
	triggerSignal(MFK_SIG_LOOKATME);
}

int  MFK_SigCorrect_Run() {
	return timer.every(50, MFK_SigCorrect_Trigger, 1);
}
void MFK_SigCorrect_Trigger() {
	triggerSignal(MFK_SIG_CORRECT);
}

int  MFK_SigWrong_Run() {
	return timer.every(100, MFK_SigWrong_Trigger, 2);
}
void MFK_SigWrong_Trigger() {
	triggerSignal(MFK_SIG_WRONG);
}

int  MFK_SigErr_Run() {
	return timer.every(100, MFK_SigErr_Trigger, 3);
}
void MFK_SigErr_Trigger() {
	triggerSignal(MFK_SIG_ERR);
}

void signal(int signalIdx) {
	signalController->start(signalIdx);
}

void pirmCallback() {
      Serial.println("pirmCallback");
  signal(MFK_SIG_LOOKATME);
}

void setup() {
	Serial.begin(9600);
	signalController = SignalController::getInstance();

	LedSignalSource *led0 = 
		new LedSignalSource(MFK_LED_PIN, 10, 2000);
    BuzzerSignalSource *buzz0 = 
		new BuzzerSignalSource(MFK_BUZZER_PIN, &timer, 10, 500);


	SignalPattern *pat = 
		new SignalPattern(MFK_SIG_LOOKATME, &timer, MFK_LookAtme_Run);
	signalController->setPattern(MFK_SIG_LOOKATME, pat);
    pat->addSignalSource(led0);
    pat->addSignalSource(buzz0);

	led0->addSigOffset(MFK_SIG_CORRECT, 5, 60);
	buzz0->addSigOffset(MFK_SIG_CORRECT, 10, 20);
	pat = new SignalPattern(MFK_SIG_CORRECT, &timer, MFK_SigCorrect_Run);
	signalController->setPattern(MFK_SIG_CORRECT, pat);
	pat->addSignalSource(led0);
    pat->addSignalSource(buzz0);

	led0->addSigOffset(MFK_SIG_WRONG, 5, 60);
	buzz0->addSigOffset(MFK_SIG_WRONG, 10, 20);
	pat = new SignalPattern(MFK_SIG_WRONG, &timer, MFK_SigWrong_Run);
	signalController->setPattern(MFK_SIG_WRONG, pat);
	pat->addSignalSource(led0);
    pat->addSignalSource(buzz0);

	led0->addSigOffset(MFK_SIG_ERR, 5, 60);
	buzz0->addSigOffset(MFK_SIG_ERR, 10, 20);
	pat = new SignalPattern(MFK_SIG_ERR, &timer, MFK_SigErr_Run);
	signalController->setPattern(MFK_SIG_ERR, pat);
	pat->addSignalSource(led0);
    pat->addSignalSource(buzz0);

	delay(3000);
	signal(MFK_SIG_ERR);

    Serial.println("after setup signal");
        pirm.registerClient(&cl);
	cl.setCallback(pirmCallback);
    Serial.println("pirm initialized");
}

void loop() {
	timer.update();
	signalController->update();
        pirm.update();
}
