

#include <Arduino.h>
#include <SerialLcd.h>


class VisualItem {
protected:
	SerialLcd *lcd;
	VisualItem *ownerMenu;
	char content[30];

public:
	VisualItem(SerialLcd *lcd);

	virtual void show(uint8_t waitInput)=0;
	virtual void exit();
};
