
/*
 * Facade pattern.
 * MFK_Hardware simplifies the usage of signalling
 * by implementing ready-to-use signal types.
 *
 */

#ifndef _MFK_HARDWARE_H_
#define _MFK_HARDWARE_H_

#include "Arduino.h"
#include "Timer.h"
#include "MFK_OutputDevice.h"
#include "MFK_InputDevice.h"
#include "SignalController.h"
#include "SignalPattern.h"
#include "BuzzerSignalSource.h"
#include "LedSignalSource.h"
#include "PIRMotion.h"

#define SIGNALLING_ENABLED 1

#define MFK_SIG_LOOKATME	0
#define MFK_SIG_CORRECT		1
#define MFK_SIG_WRONG		2
#define MFK_SIG_ERR			3

#define MFK_PIR_MOTION_PIN 11
#define MFK_BUZZER_PIN 12
#define MFK_LED_PIN    13

#define MFK_OUTDEV_RX 9
#define MFK_OUTDEV_TX 10

class MFK_Hardware: PIRMotionClient {
private:

	MFK_InputDevice<MFK_InputDeviceClient> *inpDev;
	PIRMotion<PIRMotionClient>* pirm;
	
	SoftwareSerial *ss;
	MFK_OutputDevice *outDev;

	Timer timer;
	SignalController* signalController;


	MFK_Hardware();
	MFK_Hardware(MFK_Hardware const&); // copy disabled
	void operator=(MFK_Hardware const&); // assigment disabled

	void constructSignalPatterns();

	void invokePMotCallback();
public:
	static MFK_Hardware* getInstance() {
		static MFK_Hardware hw;
		return &hw;
	};

	// software serial begin for output 
	void begin();
	
	// call in loop
	void update();
	// activate a signal pattern
	void signal(int signalIdx);


	// helper functions for signalling
	int runSignal(int sigIdx);
	void triggerSignal(int sigIdx);

	MFK_InputDevice<MFK_InputDeviceClient>* getInputDevice() 
		{ return this->inpDev; };
	MFK_OutputDevice* getOutputDevice() 
		{ return this->outDev; };
};

// SignalPattern & Timer callbacks
int  MFK_LookAtme_Run();
void MFK_LookAtMe_Trigger();
int  MFK_SigCorrect_Run();
void MFK_SigCorrect_Trigger();
int  MFK_SigWrong_Run();
void MFK_SigWrong_Trigger();
int  MFK_SigErr_Run();
void MFK_SigErr_Trigger();

#endif
