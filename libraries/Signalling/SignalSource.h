/*
 * base for signal classes
 *
 */

#ifndef _SIGNALSOURCE_H_
#define _SIGNALSOURCE_H_

#include "Arduino.h"

#define MAX_SIGNAL_PATTERN 10



class SignalSource {
protected:
	typedef struct SigOffsetS {
		int onOffset;
		int offOffset;
	} SigOffset;

	uint8_t isOn; // in an active period
	uint8_t isDisabled; // totally disabled

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
	// starts signal source in a signalling period
	virtual void on() { this->isOn = 1; };
	// stops signal source in a signalling period
	virtual void off() { this->isOn = 0; };

	// called by a signal pattern to inform for the start of a period
	virtual void trigger(); 
	// called by a signal pattern to inform for the end of pattern
	void disable() { this->isDisabled = 1; }

	// virtual void update()=0; // pure virtual
	
	// tracking of signalling in a pattern
	virtual void update(); 
};

#endif
