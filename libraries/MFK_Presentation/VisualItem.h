
/*
 * by Ozan Oner
 * base class for UI classes
 */

#ifndef _VISUAL_ITEM_H_
#define _VISUAL_ITEM_H_

#include "Arduino.h"
#include "MFK_Hardware.h"
#include "MFK_OutputDevice.h"
#include "MFK_InputDevice.h"
#include "MFK_InputDeviceClient.h"


#define BUFFER_SIZE 3 // for user input

class VisualItem: MFK_InputDeviceClient {
protected:
	char *title;
	// upper level UI item (menu)
	VisualItem *parent;
	// output device
	MFK_OutputDevice *outDev;
	// each subclass manages its own content by using that pointer
	char *content;
	
	// input buffer
	char ib[BUFFER_SIZE+1]; 
	// input idx, -1 means, buffering disabled
	int8_t ibIdx; 

	// active visual item
	static VisualItem* ACTIVE_ITEM;
	// id for ACTIVE_ITEM returned from MFK_InputDevice registration
	static int HW_INPUT_ID;
	

	// msgbox related members
	static unsigned long MSG_END_TIME;
	static uint8_t MSG_ON;
	static VisualItem* NEXT_ITEM;

	// directs input from MFK_InputDevice to ACTIVE_ITEM 
	void invokeMFKInputCallback(char);
	// evaluate keyboard input
	virtual uint8_t evaluate(char);
public:
	VisualItem(char *title);

	void setParent(VisualItem *p) { this->parent = p; };
	VisualItem* getParent() { return this->parent; };
	const char* getTitle() { return this->title; };

	static VisualItem* getActiveItem() { return VisualItem::ACTIVE_ITEM; };

	// update in loop
	virtual void update();

	// show on outputDev
	virtual void show();
	// return to parent
	virtual void exit();

	// different message box functions
	// shows a message on the outputDev and returns to 'next'
	void msgbox(char *msg, VisualItem* next);
	void msgbox(char *msg, unsigned long duration, VisualItem* next);
	// signalType from MFK_Hardware.h MFK_SIG_*
	void msgbox(char *msg, unsigned long duration, \
			uint8_t signalType, VisualItem* next);
	void msgboxerr(char *msg, VisualItem* next);
};



#endif
