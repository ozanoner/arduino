

Book::Book() {
	this->chapterCnt =0;
	for(int i=0; i<5; i++)
		this->chapter[i]=NULL;
}

void Book::addChapter(Chapter *c) {
	if(this->chapterCnt >= 10)
		return;
	this->chapter[this->chapterCnt++]=c;
}

Chapter* Book::getChapter(uint8_t id) {
	for(int i=0; i<this->chapterCnt; i++) {
		if(this->chapter[i]->getId() == id) 
			return this->chapter[i];
	}
	return NULL;
}
