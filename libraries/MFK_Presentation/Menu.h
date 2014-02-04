

#ifndef _MENU_H_
#define _MENU_H_

#include "Arduino.h"
#include "VisualItem.h"

#define MENU_CONTENT_SIZE 28

class Menu: public VisualItem {
private:
	VisualItem *menuItem[5];
	uint8_t itemCnt;
	char menuContent[MENU_CONTENT_SIZE];
public:
	Menu(char *title);
	uint8_t addMenuItem(VisualItem *subItem);
	void show();
	uint8_t evaluate(char c);
};

#endif
