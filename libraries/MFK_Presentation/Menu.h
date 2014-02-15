
/*
 * by Ozan Oner
 *
 * Menu for user to select content
 */


#ifndef _MENU_H_
#define _MENU_H_

#include "Arduino.h"
#include "VisualItem.h"

#define MENU_CONTENT_SIZE 32

class Menu: public VisualItem {
private:
	// sub items
	VisualItem *menuItem[5];
	// number of sub items
	uint8_t itemCnt;
	// base->content = this->menuContent
	char menuContent[MENU_CONTENT_SIZE];

	// evaluate user input
	uint8_t evaluate(char c);
public:
	Menu(char *title);
	// add sub-item
	uint8_t addMenuItem(VisualItem *subItem);
	// show on display
	void show();
};

#endif
