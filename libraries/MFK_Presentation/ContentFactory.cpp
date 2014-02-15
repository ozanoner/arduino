
#include "ContentFactory.h"

/*
FLASH_STRING_ARRAY(funAnswer,\
		"What is your name?",\
		"What is your father's name?",\
		"What is your mother's name?",\
		"How are you?",\
		"What day is it today?",\
		"Days of the week",\
		"Your favorite color?",\
		"Your favorite toy?",\
		"Your favorite animal?",\
		"Your favorite character?",\
		"Count to 20");


FLASH_STRING_ARRAY(funSing,
		"song 1",
		"song 2");

FLASH_STRING_ARRAY(funMove,
		"Jump 10 times",
		"Run",
		"Call your father",
		"Walk around",
		"Bring me a toy",
		"Tidy up your room",
		"Open the door",
		"Close the door",
		"Find a color pencil",
		"Draw a picture",
		"Close your eyes",
		"Brush your hair",
		"Brush your teeth",
		"Hands up",
		"Stand up",
		"Sit down",
		"Stand up and sit down",
		"Go to the kitchen",
		"Go to your room",
		"Read a book");
*/


ContentFactory::ContentFactory() {
	for(int i=0; i<5; i++)  // operation type
		for(int j=0; j<3; j++) // content level
			this->contentProvider[i][j] = NULL;
	randomSeed(analogRead(MFK_RANDOM_SEED_PIN));
}

// addition contents
void ContentP_0_0(char *content, int &answer) {
	int i = random(2, 11);
	if(i*2 == answer)
		i--;
	sprintf(content, "%d+%d=", i, i);
	answer=i*2;
}

void ContentP_0_1(char *content, int &answer) {
	int i1 = random(2,11);
	int i2 = random(2,11);
	sprintf(content, "%d+%d=", i1, i2);
	answer=i1+i2;
}

void ContentP_0_2(char *content, int &answer) {
	int i1 = random(0, 50);
	int i2 = random(0, 50);
	sprintf(content, "%d+%d=", i1, i2);
	answer=i1+i2;
}

// subtraction contents
void ContentP_1_0(char *content, int &answer) {
	int i1 = random(0, 5);
	int i2 = random(0, 5);
	if(i1 == answer)
		i1++;
	sprintf(content, "%d-%d=", i1+i2, i2);
	answer=i1;
}

void ContentP_1_1(char *content, int &answer) {
	int i1 = random(0, 10);
	int i2 = random(5, 10);
	if(i1 == answer)
		i1++;
	sprintf(content, "%d-%d=", i1+i2, i2);
	answer=i1;
}

void ContentP_1_2(char *content, int &answer) {
	int i1 = random(10, 50);
	int i2 = random(10, 50);
	sprintf(content, "%d-%d=", i1+i2, i2);
	answer=i1;
}

// fun contents
/*
void ContentP_4_0(char *content, int &answer) {
	int idx = random(0, funAnswer.count());
	if(funAnswer[idx].length()>30)
		funAnswer[idx].copy(content, 30);
	else
		funAnswer[idx].copy(content);
}

void ContentP_4_1(char *content, int &answer) {
	int idx = random(0, funSing.count());
	if(funSing[idx].length()>30)
		funSing[idx].copy(content, 30);
	else
		funSing[idx].copy(content);
}

void ContentP_4_2(char *content, int &answer) {
	int idx = random(0, funMove.count());
	if(funMove[idx].length()>30)
		funMove[idx].copy(content, 30);
	else
		funMove[idx].copy(content);
}
*/

const ContentProvider* ContentFactory::getContentProvider(OperationTypeEnum op,\
	   	ContentLevelEnum level) {
	if(this->contentProvider[op][level] != NULL)
		return this->contentProvider[op][level];

	ContentProvider *p=NULL;

	switch(op) {
		case Addition:
			switch(level) {
				case Level1Content:
					p = new ContentProvider(ContentP_0_0);
					break;
				case Level2Content:
					p = new ContentProvider(ContentP_0_1);
					break;
				case Level3Content:
					p = new ContentProvider(ContentP_0_2);
					break;
				default:
					break;
			}
			break;
		case Subtraction:	
			switch(level) {
				case Level1Content:
					p = new ContentProvider(ContentP_1_0);
					break;
				case Level2Content:
					p = new ContentProvider(ContentP_1_1);
					break;
				case Level3Content:
					p = new ContentProvider(ContentP_1_2);
					break;
				default:
					break;
			}
			break;
		case Multiplication:
			break;
		case Division:
			break;
		case Fun:
			/*
			switch(level) {
				case Level1Content:
					p = new ContentProvider(ContentP_4_0);
					break;
				case Level2Content:
					p = new ContentProvider(ContentP_4_1);
					break;
				case Level3Content:
					p = new ContentProvider(ContentP_4_2);
					break;
				default:
					break;
			}
			*/
			break;
		default:
			break;
	}
	Serial.println(F("ContentProvider created"));
	return p;
}

