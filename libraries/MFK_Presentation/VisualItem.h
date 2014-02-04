
/*
 * Command pattern.
 * ACTIVE_ITEM receives user inputs with its 'invokeMFKInputCallback' function 
 * and takes action accordingly. 'evaluate' function differs 
 * for each receiver implementation.
 */

#ifndef _VISUAL_ITEM_H_
#define _VISUAL_ITEM_H_

#include "Arduino.h"
#include "MFK_Hardware.h"
#include "MFK_OutputDevice.h"
#include "MFK_InputDevice.h"
#include "MFK_InputDeviceClient.h"


#define BUFFER_SIZE 3

class VisualItem: MFK_InputDeviceClient {
protected:
	char *title;
	VisualItem *parent;
	MFK_OutputDevice *outDev;
	char *content;
	
	// input buffer
	char ib[BUFFER_SIZE+1]; 
	// input idx, -1 means, buffering disabled
	int8_t ibIdx; 

	// active visual item
	static VisualItem* ACTIVE_ITEM;
	// id for ACTIVE_ITEM returned from MFK_InputDevice registration
	static int HW_INPUT_ID;
	

	static unsigned long MSG_END_TIME;
	static uint8_t MSG_ON;
	static VisualItem* NEXT_ITEM;

	// directs input to ACTIVE_ITEM from MFK_InputDevice
	void invokeMFKInputCallback(char);

	void parentShow();
public:
	VisualItem(char *title);

	void setParent(VisualItem *p) {
		this->parent = p;
	};
	VisualItem* getParent() {
		return this->parent;
	};
	char *getTitle();

	static VisualItem* getActiveItem();

	void update();

	virtual uint8_t evaluate(char);
	virtual void show();
	virtual void exit();

	void msgbox(char *msg, VisualItem* next);
	void msgbox(char *msg, unsigned long duration, VisualItem* next);
	// signalType from MFK_Hardware.h MFK_SIG_*
	void msgbox(char *msg, unsigned long duration, uint8_t signalType, VisualItem* next);
	void msgboxerr(char *msg, VisualItem* next);
};



#endif
