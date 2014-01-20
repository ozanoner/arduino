
enum ChapterTypeEnum {
	NormalChapter,
	QuizChapter,
	FunChapter
};

class Chapter {
protected:
	static char CONTENT[32];
	static char MESS[32];
	static int ANSWER;

	uint8_t id;
	ChapterTypeEnum type;

	uint8_t tryCnt;
	uint8_t successCnt;
	uint8_t totCnt;

	ContentProvider *contentProvider[5];
	uint8_t cpCnt;
public:
	Chapter(uint8_t id, ChapterTypeEnum type);
	void addContentProvider(ContentProvider *cp);

	char *getMessage(); // returns last message 
	uint8_t getId();
	ChapterTypeEnum getChapterType();

	void start();
	char* next(); // returns content
	uint8_t evaluate(char *userInput); // returns if successful
	char*  end(); // returns message if needed
};
