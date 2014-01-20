

#include <Arduino.h>
#include <VisualItem.h>
#include <Chapter.h>

#define QUIZ_DURATION 3 // in minutes

class Page: public VisualItem {
private:
	Chapter *chapter;
	ChapterTypeEnum chapterType;
	unsigned long start;
public:
	Page(SerialLcd *lcd, Book *b, uint8_t chapterId);
	void evaluate(char *userInput);
};
