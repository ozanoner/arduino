
#include "Page.h"

Page::Page(char *title): VisualItem(title) {
	this->chapter=NULL;
}

Page::Page(char *title, Timer* t): VisualItem(title) {
	this->chapter=NULL;
	this->timer=t;
	this->eventId=-1;
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
	VisualItem::show();

	// lazy instantiation of chapter
	if(this->chapter==NULL) {
		this->chapter = Chapter::createChapter(this->chapterType,
				this->opType,
				this->contentLevel);
		if(this->chapter==NULL) {
			this->msgboxerr("no data", this->parent);
			// this->parentShow();
			return;
		}
		Serial.println(F("chapter created"));
		this->chapter->start();
	}

	this->ibIdx = this->chapterType == Chapter::FunChapter? -1:0;
	if(this->chapterType==Chapter::QuizChapter && this->eventId<0) {
		this->eventId = this->timer->after(QUIZ_TIMEOUT*60*1000, \
				timerCallbackForQuizEnd);
		if(this->eventId<0) {
			this->msgboxerr("Timer failed", this->parent);
			// this->parentShow();
			return;
		}
	}
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
		// this->show();
	}
	return 1;
}

void Page::quizEnded() {
	this->msgbox(this->chapter->getMessage(), 5000, this->parent);
	// this->parentShow();
}

void timerCallbackForQuizEnd() {
	Page *p = (Page *)VisualItem::getActiveItem();
	if(p!=NULL)
		p->quizEnded();
}
