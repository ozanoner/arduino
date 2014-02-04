

#ifndef _PAGE_H_
#define _PAGE_H_

#include "Arduino.h"
#include "VisualItem.h"
#include "Chapter.h"

#define QUIZ_TIMEOUT 3 // in minutes

class Page: public VisualItem {
protected:
	Chapter* chapter;
	Chapter::ChapterTypeEnum chapterType;
	ContentFactory::OperationTypeEnum opType;
	ContentFactory::ContentLevelEnum contentLevel;
	Timer* timer;
	int eventId;
public:
	Page(char *title);
	// timer is to detect quiz end
	Page(char *title, Timer* t);

	// will be used to create chapter 
	void setChapterProperties(Chapter::ChapterTypeEnum, \
			ContentFactory::OperationTypeEnum, \
			ContentFactory::ContentLevelEnum);
			

	virtual uint8_t evaluate(char c);
	virtual void show();
	
	// will be called in timer callback
	void quizEnded();
};

void timerCallbackForQuizEnd();

#endif
