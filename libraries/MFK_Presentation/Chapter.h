/*
 * Bridge pattern. 
 * Chapter provides abstraction for client.
 * Underlying ContentProvider implementation varies.
 */

#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include "Arduino.h"
#include "ContentProvider.h"
#include "ContentFactory.h"

class Chapter {
public:
	enum ChapterTypeEnum {
		NormalChapter,
		FunChapter,
		QuizChapter
	};
	Chapter(ChapterTypeEnum, ContentProvider *);
	void addContentProvider(ContentProvider*);

	static Chapter* createChapter(Chapter::ChapterTypeEnum, \
			ContentFactory::OperationTypeEnum, \
			ContentFactory::ContentLevelEnum);

	char* getMessage(); // returns last message 
	ChapterTypeEnum getType();

	// call when a page is displayed first time
	virtual void start();
	// call before requesting stats with getMessage
	virtual void end();
	char* next(); // returns content
	uint8_t evaluate(char *userInput); // returns 1 if successful
private:
	static char CONTENT[32];
	static char MESS[32];
	static int ANSWER;

	ChapterTypeEnum chapterType;
	// at least one content
	// quizes may have more
	ContentProvider* contentP[5]; 
	// content provider count
	int cpCount;

	uint8_t tryCnt;
	uint8_t correctCnt;
	uint8_t totalCnt;
};

#endif
