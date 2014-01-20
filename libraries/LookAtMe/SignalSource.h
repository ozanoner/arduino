/*
 * base for signal classes
 *
 */

#include <Arduino.h>

#ifndef _SIGNALSOURCE_H_
#define _SIGNALSOURCE_H_

class SignalSource {
protected:
	uint8_t isOn; // in an active period
	uint8_t isDisabled; // totally disabled

	// offset values to calculate next active period
	int onOffset;
	int offOffset;
	// each SignalSource derivation decides its own action
	// between nextOn & nextOff
	unsigned long nextOn;
	unsigned long nextOff;

public:
	SignalSource(int onOffset, int offOffset); 

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
