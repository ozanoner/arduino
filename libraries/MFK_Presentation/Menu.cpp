
#include "Menu.h"

Menu::Menu(char *title): VisualItem(title) {
	for(int i=0; i<5; i++)
		this->menuItem[i]=NULL;
	this->itemCnt=0;
	this->content = this->menuContent;
	memset(this->content, 0, MENU_CONTENT_SIZE);
}

uint8_t Menu::addMenuItem(VisualItem *item) {
	if(this->itemCnt>=5)
		return -1;
	if(item==NULL)
		return -2;
	item->setParent(this);
	this->menuItem[this->itemCnt++] = item;
	return this->itemCnt;
}


void Menu::show() {
	if(VisualItem::MSG_ON)
		return;
	VisualItem::show();
	if(!this->content[0]) {
		char *s=this->content;
		char *title;
		for(int i=0; i<this->itemCnt; i++) {
			title = this->menuItem[i]->getTitle();
			if(strlen(title)+strlen(s)>=MENU_CONTENT_SIZE)
				break;
			sprintf(s, "(%d)%s ",i+1,title);
			s+=strlen(s);
		}
	}
	this->outDev->print(this->content);
}

uint8_t Menu::evaluate(char c) {
	if(VisualItem::MSG_ON)
		return 1;
	if(VisualItem::evaluate(c))
		return 1;

	uint8_t idx = c-'1';
	if(idx<0 || idx>=this->itemCnt) {
		this->msgboxerr("invalid selection", this);
		return 1;
	}
	this->menuItem[idx]->show();
	return 1;
}

