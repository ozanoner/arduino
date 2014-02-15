
/*
 * by Ozan Oner
 *
 * unified interface for hardware
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
#include "MFK_Pins.h"

#define SIGNALLING_ENABLED 1
#define MOTION_DETECT_ENABLED 1

// named signal indices
// use with signal() function
#define MFK_SIG_LOOKATME	0
#define MFK_SIG_CORRECT		1
#define MFK_SIG_WRONG		2
#define MFK_SIG_ERR			3

#define MFK_SIG_DEFAULT_PERIOD 100
#define MFK_SIG_LOOKATME_PERIOD 3000

// PIR defs
#define PIR_REPORT_INTERVAL 5 // secs
#define PIR_LAG 60 // secs



class MFK_Hardware: PIRMotionClient {
private:

	// unified keyboard
	MFK_InputDevice<MFK_InputDeviceClient> *inpDev;
	// PIR motion sensor
	PIRMotion<PIRMotionClient>* pirm;
	
	// software serial for serial LCD
	SoftwareSerial *ss;
	// output device which is enhanced serial LCD
	MFK_OutputDevice *outDev;

	// timer for signal controller
	Timer timer;
	SignalController* signalController;


	// private constructor to achieve singleton pattern
	MFK_Hardware();
	MFK_Hardware(MFK_Hardware const&); // copy disabled
	void operator=(MFK_Hardware const&); // assigment disabled

	// signal pattern construction
	void constructSignalPatterns();

	// PIR sensor callback, which is defined in PIRMotionClient
	void invokePMotCallback();
public:
	// static method to get the instance 
	static MFK_Hardware* getInstance() {
		static MFK_Hardware hw;
		return &hw;
	};

	// initializes the MFK_Hardware
	void begin();
	
	// call in loop
	void update();
	// activate a signal pattern
	void signal(int signalIdx);


	// helper functions for signalling
	int runSignal(int sigIdx);
	void triggerSignal(int sigIdx);

	// input device getter
	MFK_InputDevice<MFK_InputDeviceClient>* getInputDevice() 
		{ return this->inpDev; };
	// output device getter
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
