/*
 * by Ozan Oner
 * base class for signal sources
 */

#ifndef _SIGNALSOURCE_H_
#define _SIGNALSOURCE_H_

#include "Arduino.h"

#define MAX_SIGNAL_PATTERN 10

class SignalSource {
protected:
	// typedef for offsets structure in a signalling period
	typedef struct SigOffsetS {
		int onOffset;
		int offOffset;
	} SigOffset;

	// means that the time is between nextOn & nextOff
	uint8_t isOn; 
	// signal source is disabled
	uint8_t isDisabled; 

	// holds for each signal pattern
	SigOffset *offset[MAX_SIGNAL_PATTERN];

	// offset values to calculate next active period
	int onOffset;
	int offOffset;
	
	// each SignalSource derivation decides its own action
	// between nextOn & nextOff
	unsigned long nextOn;
	unsigned long nextOff;

public:
	// first offset idx will be 0
	SignalSource(int onOffset, int offOffset); 
	// adds new signal offset for a pattern
	void addSigOffset(int sigIdx, int onOffset, int offOffset);
	// activates a pattern
	void activate(int sigIdx);

	uint8_t getIsOn() { return this->isOn; };
	// starts signal source at nextOn
	virtual void on() { this->isOn = 1; };
	// stops signal source at nextOff
	virtual void off() { this->isOn = 0; };

	// called by a signal pattern to inform for the start of a period
	virtual void trigger(); 
	// called by a signal pattern to inform for the end of pattern
	void disable() { this->isDisabled = 1; }

	// update in loop
	virtual void update(); 
};

#endif
