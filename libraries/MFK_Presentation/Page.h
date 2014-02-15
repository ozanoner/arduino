/*
 * by Ozan Oner
 *
 * UI class to show content
 */


#ifndef _PAGE_H_
#define _PAGE_H_

#include "Arduino.h"
#include "VisualItem.h"
#include "Chapter.h"

#define QUIZ_TIMEOUT 300000 // in ms (5mins)

class Page: public VisualItem {
public:
	Page(char *title);

	// will be used to create chapter 
	void setChapterProperties(Chapter::ChapterTypeEnum, \
			ContentFactory::OperationTypeEnum, \
			ContentFactory::ContentLevelEnum);
			
	// show on lcd
	void show();

	// update in loop
	void update();

protected:
	// content related variables
	Chapter* chapter;
	Chapter::ChapterTypeEnum chapterType;
	ContentFactory::OperationTypeEnum opType;
	ContentFactory::ContentLevelEnum contentLevel;
	
	// quiz time tracking
	static unsigned long QUIZ_END_TIME;
	static uint8_t IN_QUIZ;

	// initializes above quiz variables
	void initQuiz();

	// user input evaluation
	virtual uint8_t evaluate(char c);
	
};

#endif
