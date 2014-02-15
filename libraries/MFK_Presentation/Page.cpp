
#include "Page.h"

unsigned long Page::QUIZ_END_TIME=0;
uint8_t Page::IN_QUIZ=0;

Page::Page(char *title): VisualItem(title) {
	this->chapter=NULL;
}

void Page::setChapterProperties(Chapter::ChapterTypeEnum ct,\
		ContentFactory::OperationTypeEnum ot, \
		ContentFactory::ContentLevelEnum cl) {
	this->chapterType = ct;
	this->opType = ot;
	this->contentLevel = cl;
}

void Page::show() {
	if(VisualItem::MSG_ON)
		return;
	uint8_t newshow = VisualItem::ACTIVE_ITEM == this? 0:1;
	VisualItem::show();

	// lazy instantiation of chapter
	if(this->chapter==NULL) {
		this->chapter = Chapter::createChapter(this->chapterType,
				this->opType,
				this->contentLevel);
		if(this->chapter==NULL) {
			this->msgboxerr("no data", this->parent);
			return;
		}
		Serial.println(F("chapter created"));
	}
	if(newshow) {
		this->chapter->start();
		this->initQuiz();
	}

	this->ibIdx = this->chapterType == Chapter::FunChapter? -1:0;

	char *mess = this->chapter->next();
	if(mess==NULL || !*mess) {
		mess = this->chapter->getMessage();
		if(mess!=NULL && *mess)
			this->msgboxerr(mess, this->parent);
		else
			this->msgboxerr("empty content", this->parent);
		// this->parentShow();
		return;
	}

	this->content = mess;
	this->outDev->print(this->content);
}

uint8_t Page::evaluate(char c) {
	if(VisualItem::MSG_ON)
		return 1;
	if(VisualItem::evaluate(c)) {
		Serial.println(F("evaluate returned from VisualItem"));
		return 1;
	}

	if(mfkIsPrintable(c)) {
		if(this->ibIdx>=0 && this->ibIdx<BUFFER_SIZE) {
			this->ib[this->ibIdx++]=c;
			this->outDev->write(c);
		}
	}
	else if(c==KEY_ENTER && this->ibIdx>0) {
		uint8_t success = this->chapter->evaluate(this->ib);
		char *mess = this->chapter->getMessage();
		if(mess && *mess) {
			if(success) {
				if(this->chapterType==Chapter::NormalChapter) {
					this->msgbox(mess, 2000, MFK_SIG_CORRECT, this);
				}
			}
			else {
				this->msgbox(mess, 2000, MFK_SIG_WRONG, this);
			}
		}
	}
	return 1;
}

void Page::update() {
	VisualItem::update();
	if(VisualItem::MSG_ON)
		return;

	if(Page::IN_QUIZ && Page::QUIZ_END_TIME<millis()) {
		this->chapter->end();
		this->msgbox(this->chapter->getMessage(), 5000, this->parent);
		Page::IN_QUIZ=0;
	}
}

void Page::initQuiz() {
	if(this->chapterType == Chapter::QuizChapter) {
		Page::QUIZ_END_TIME=millis()+QUIZ_TIMEOUT;
		Page::IN_QUIZ=1;
	}
	else {
		Page::IN_QUIZ=0;
	}
}
