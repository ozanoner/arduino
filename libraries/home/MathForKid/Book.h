

class Book {
private:
	Chapter *chapter[10];
	int chapterCnt;
public:
	Book();
	void addChapter(Chapter *c);
	Chapter* getChapter(uint8_t id);
}
