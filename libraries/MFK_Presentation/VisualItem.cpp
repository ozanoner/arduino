
#include "VisualItem.h"

VisualItem* VisualItem::ACTIVE_ITEM=NULL;
int VisualItem::HW_INPUT_ID=-1;

unsigned long VisualItem::MSG_END_TIME=0;
uint8_t VisualItem::MSG_ON=0;
VisualItem* VisualItem::NEXT_ITEM=NULL;

VisualItem::VisualItem(char *title) {
	this->parent = NULL;
	this->title=title;
	this->outDev = MFK_Hardware::getInstance()->getOutputDevice();
	this->content=NULL;
}

void VisualItem::show() {
	if(VisualItem::MSG_ON)
		return;
	memset(this->ib,0,BUFFER_SIZE);
	this->ibIdx=0;
	if(this != VisualItem::ACTIVE_ITEM) { 
		VisualItem::ACTIVE_ITEM = this;
		MFK_InputDevice<MFK_InputDeviceClient> *d = \
			  MFK_Hardware::getInstance()->getInputDevice();
		d->unregisterClient(VisualItem::HW_INPUT_ID);
		VisualItem::HW_INPUT_ID = d->registerClient(this);
	}
}

void VisualItem::invokeMFKInputCallback(char c) {
	if(VisualItem::MSG_ON)
		return;
	this->evaluate(c);
}

void VisualItem::exit() {
	if(VisualItem::MSG_ON)
		return;
	if(this->parent != NULL)
		this->parent->show();
}


uint8_t VisualItem::evaluate(char c)  {
	if(VisualItem::MSG_ON)
		return 1;
	uint8_t retval=0;
	switch(c) {
		case KEY_ESC:
			this->exit();
			retval=1;
			break;
		case KEY_BS:
			if(this->ibIdx>0) {
				this->ib[--this->ibIdx]=0;
				this->outDev->del();
			}
			retval=1;
			break;
		default:
			break;
	}
	return retval;
}

void VisualItem::msgbox(char *msg, unsigned long duration, 
		uint8_t signalType, VisualItem* next) {
	if(VisualItem::MSG_ON)
		return;

	VisualItem::MSG_END_TIME = millis()+duration;
	VisualItem::MSG_ON = 1;
	VisualItem::NEXT_ITEM = next;

	this->outDev->print(msg, 1);
	MFK_Hardware::getInstance()->signal(signalType);
}


void VisualItem::msgbox(char *msg, unsigned long duration, VisualItem* next) {
	this->msgbox(msg, duration, -1, next);
}

void VisualItem::msgbox(char *msg, VisualItem* next) {
	this->msgbox(msg, 3000, -1, next);
}

void VisualItem::msgboxerr(char *msg, VisualItem* next) {
	this->msgbox(msg, 3000, MFK_SIG_ERR, next); 
}

void VisualItem::update() {
	if(VisualItem::MSG_ON) {
		// Serial.println(F("in VisualItem::update"));
		if(VisualItem::MSG_END_TIME>millis())
			return;
		VisualItem::MSG_ON=0;
		if(VisualItem::NEXT_ITEM!=NULL) {
			Serial.println(F("showing next item"));
			VisualItem::NEXT_ITEM->show();
		}
		else {
			Serial.println(F("no next item"));
		}
	}
}
