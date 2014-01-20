
#include <VisualItem.h>

VisualItem::VisualItem(SerialLcd *lcd) {
	this->lcd = lcd;
	memset(this->content, 0, 30);
}

void VisualItem::exit() {
	if(this->ownerMenu != NULL)
		this->ownerMenu->show();
}
