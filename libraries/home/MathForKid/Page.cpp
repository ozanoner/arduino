
#include <Page.h>

Page::Page(SerialLcd *lcd, Book *b, uint8_t chapterId): \
		VisualItem(lcd) {
	this->chapter = b->getChapter(chapterId);
	if(this->chapter == NULL)
		return;
	this->chapterType = this->chapter->getChapterType();
}

void Page::show(uint8_t waitInput) {
	if(this->chapter==NULL)
		return;
	this->lcd->print(this->chapter->next());
	this->lcd->setBlinkCursor(waitInput);
}

void Page::evaluate(char *userInput) {

	// todo: should be coded acc.to ChapterType
	if(this->chapter==NULL)
		return;
	int len = strlen(userInput);
	if(!len)
		return;
	if(userInput[len-1] == '*')
		this->exit();
	else if(userInput[len-1] == '#') {
		userInput[len-1]=0;
		uint8_t isCorrect = this->chapter->evaluate(userInput);
		char *mess = this->chapter->getMessage();
		if(*mess) {
			if(isCorrect) {
				// activate success signal pattern
			}
			else {
				// activate fail signal pattern
			}
			this->lcd->print(mess);
			this->lcd->setBlinkCursor(0);
			delay(3000);
		}
	}
	this->show();
}
