

Menu::Menu(SerialLcd *lcd):VisualItem(lcd) {
	for(int i=0; i<5; i++)
		this->menuItem[i]=NULL;
	this->itemCnt=0;
}

uint8_t Menu::addMenuItem(char *name, VisualItem *subItem) {
	if(this->itemCnt>=5)
		return -1;
	if(name == NULL || subItem == NULL)
		return -2;
	MenuItem *item = new MenuItem;
	item->name = name;
	item->visItem = subItem;
	subItem->ownerMenu = this;
	this->menuItem[this->itemCnt] = item;
	return this->itemCnt++;
}

void Menu::selectMenuItem(uint8_t itemId) {
	if(this->itemCnt>=5)
		return;
	this->menuItem[itemId]->visItem->show();
}

void Menu::show(uint8_t waitInput) {
	if(!this->content[0]) {
		char *s=this->content;
		for(int i=0; i<this->itemCnt; i++) {
			sprintf(s, "(%d)%s ",i,this->menuItem[i]->name);
			s=this->content+strlen(s);
		}
	}
	this->lcd->print(this->content);
	this->lcd->showBlinkCursor(1);
}
