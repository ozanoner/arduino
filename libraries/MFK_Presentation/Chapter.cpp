
#include "Chapter.h"

char Chapter::CONTENT[32];
char Chapter::MESS[32];
int  Chapter::ANSWER;

Chapter::Chapter(Chapter::ChapterTypeEnum t, const ContentProvider* cp) {
	this->chapterType = t;
	for(int i=0; i<5; i++)
		this->contentP[i]=NULL;
	this->cpCount=0;
	if(cp!=NULL) {
		this->contentP[0] = cp;
		this->cpCount=1;
	}
}

Chapter* Chapter::createChapter(Chapter::ChapterTypeEnum ct, \
			ContentFactory::OperationTypeEnum ot, \
			ContentFactory::ContentLevelEnum cl) {
	ContentFactory *cf = ContentFactory::getInstance();
	if(ct==Chapter::QuizChapter)
		cl=ContentFactory::Level1Content;
	const ContentProvider *cp = cf->getContentProvider(ot, cl);
	if(cp==NULL)
		return NULL;
	Serial.print(F("content created "));
	Serial.print(ct);
	Serial.print(" ");
	Serial.print(ot);
	Serial.print(" ");
	Serial.println(cl);
	Chapter *c = new Chapter(ct, cp);
	if(ct==Chapter::QuizChapter) {
		for(int i=1; i<3; i++) {
			cl = (ContentFactory::ContentLevelEnum)i;
			cp = cf->getContentProvider(ot, cl);
			if(cp!=NULL)
				c->addContentProvider(cp);
		}
	}
	return c;
}

void Chapter::addContentProvider(const ContentProvider* cp) {
	if(this->cpCount>=5 || cp==NULL)
		return;
	this->contentP[this->cpCount++]=cp;
}

char* Chapter::next() {
	char *retval=NULL;
	int cIdx=0;
	/*
	Serial.print(F("chapter type: "));
	Serial.println(this->chapterType);
	*/
	/*
	Serial.print(F("stats: "));
	Serial.print(this->totalCnt);
	Serial.print("/");
	Serial.print(this->correctCnt);
	Serial.print(" ");
	Serial.println(this->tryCnt);
	*/

	switch(this->chapterType) {
		case NormalChapter:
			if(this->tryCnt==0) {
				Serial.println(F("calling getContent"));
				retval = this->contentP[0]->getContent(Chapter::CONTENT, \
					Chapter::ANSWER);
			}
			else {
				retval = Chapter::CONTENT;
			}
			break;
		case FunChapter:
			retval = this->contentP[0]->getContent(Chapter::CONTENT, \
				Chapter::ANSWER);
			break;
		case QuizChapter:
			cIdx= this->totalCnt/10;
			if(cIdx>=this->cpCount)
				cIdx=this->cpCount-1;
			retval = this->contentP[cIdx]->getContent(Chapter::CONTENT, \
				Chapter::ANSWER);
			break;
		default:
			break;
	}
	return retval;
}

uint8_t Chapter::evaluate(char* userInput) {
	int val;
	uint8_t isCorrect=0;
	if(this->chapterType==Chapter::FunChapter) 
		return 1;
	else {
		if(userInput==NULL || !*userInput) {
			Serial.println(F("no user input"));
			return 0;
		}
		val = atoi(userInput);
		isCorrect = val==Chapter::ANSWER? 1:0;
		if(isCorrect) {
			this->correctCnt++;
			this->totalCnt++;
			this->tryCnt=0;
			sprintf(Chapter::MESS, "GOOD!");
		}
		else {
			if(this->chapterType==Chapter::NormalChapter) {
				if(++this->tryCnt<3)
					sprintf(Chapter::MESS, "Try again!");
				else {
					sprintf(Chapter::MESS, "Answer is %d", Chapter::ANSWER);
					this->tryCnt=0;
					this->totalCnt++;
				}
			} 
			else {
				sprintf(Chapter::MESS, "Answer is %d", Chapter::ANSWER);
				this->totalCnt++;
			}
		}
	}
	return isCorrect;
}

void Chapter::start() {
	this->tryCnt=0;
	this->correctCnt=0;
	this->totalCnt=0;
	Serial.println(F("chapter started"));
}

void Chapter::end() {
	sprintf(Chapter::MESS,\
		   "%d / %d", this->totalCnt, this->correctCnt);
}
