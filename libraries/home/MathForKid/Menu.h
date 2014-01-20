
#include <Arduino.h>
#include <VisualItem.h>


typedef struct MenuItemS {
	char *name;
	VisualItem *visItem; // related menu or page
} MenuItem;

class Menu: public VisualItem {
private:
	MenuItem *menuItem[5];
	uint8_t itemCnt;
public:
	Menu();
	uint8_t addMenuItem(char *name, VisualItem *subItem);
	void selectMenuItem(uint8_t itemId);
};
