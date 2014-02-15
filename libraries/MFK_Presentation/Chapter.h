/*
 * by Ozan Oner
 * intermediate class between Page and ContentProvider
 */

// TODO: add stats to the beginning of content for normal chapter

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

	// to create a chapter
	static Chapter* createChapter(Chapter::ChapterTypeEnum, \
			ContentFactory::OperationTypeEnum, \
			ContentFactory::ContentLevelEnum);
	
	char* getMessage() const { return Chapter::MESS; };
	const ChapterTypeEnum getType() const { return this->chapterType; };

	// call when a page is displayed first time
	virtual void start();
	// call before requesting stats with getMessage
	virtual void end();
	// returns content
	char* next(); 
	// evaluate user input
	// returns 1 if successful
	uint8_t evaluate(char *userInput); 
private:
	static char CONTENT[32];
	static char MESS[32];
	static int ANSWER;

	Chapter(ChapterTypeEnum, const ContentProvider*);
	void addContentProvider(const ContentProvider*);

	ChapterTypeEnum chapterType;
	// a chapter has to have one content at minimum
	// quizes have more
	const ContentProvider* contentP[5]; 
	// content provider count
	int cpCount;

	// stats
	uint8_t tryCnt;
	uint8_t correctCnt;
	uint8_t totalCnt;
};

#endif
