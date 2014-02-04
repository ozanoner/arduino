

#include <Arduino.h>
#include <avr/pgmspace.h>

#include <ClientOwner.h>
#include <AdKeyboard.h>
#include <AdKeyboardClient.h>
#include <Keypad2.h>
#include <Keypad2Client.h>
#include <MFK_InputDevice.h>
#include <MFK_InputDeviceClient.h>
#include <SoftwareSerial.h>
#include <SerialLcd.h>

#include <Timer.h>
#include <SignalController.h>
#include <SignalPattern.h>
#include <BuzzerSignalSource.h>
#include <LedSignalSource.h>
#include <PIRMotion.h>

#include <Flash.h>
#include <ContentFactory.h>
#include <Chapter.h>
#include <Menu.h>
#include <Page.h>
#include <ContentProvider.h>
#include <VisualItem.h>

MFK_Hardware* hw;
Menu* mainMenu;

void setup() {
	Serial.begin(9600);
  
	hw = MFK_Hardware::getInstance();
	hw->begin();

	CreateUI();
	mainMenu->show();
}

void loop() {
	hw->update();
	VisualItem *v = VisualItem::getActiveItem();
	if(v!=NULL)
		v->update();
}

void CreateUI() {
	mainMenu = new Menu("main");

	// addition
	Menu* m = new Menu("+");
	mainMenu->addMenuItem(m);

	Page* p = new Page((char *)"L1");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Addition, ContentFactory::Level1Content);
	m->addMenuItem(p);

	p = new Page((char *)"L2");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Addition, ContentFactory::Level2Content);
	m->addMenuItem(p);

	p = new Page((char *)"L3");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Addition, ContentFactory::Level3Content);
	m->addMenuItem(p);

/*
	p = new Page((char *)"Q");
	p->setChapterProperties(Chapter::QuizChapter, \
			ContentFactory::Addition, ContentFactory::Level1Content);
	m->addMenuItem(p);
*/

	// subtraction
	m = new Menu("-");
	mainMenu->addMenuItem(m);

	p = new Page((char *)"L1");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Subtraction, ContentFactory::Level1Content);
	m->addMenuItem(p);

	p = new Page((char *)"L2");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Subtraction, ContentFactory::Level2Content);
	m->addMenuItem(p);
/*
	p = new Page((char *)"L3");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Subtraction, ContentFactory::Level3Content);
	m->addMenuItem(p);

	p = new Page((char *)"Q");
	p->setChapterProperties(Chapter::QuizChapter, \
			ContentFactory::Subtraction, ContentFactory::Level1Content);
	m->addMenuItem(p);
*/
	// fun
/*
	m = new Menu("Fun");
	mainMenu->addMenuItem(m);

	p = new Page((char *)"Answer");
	p->setChapterProperties(Chapter::FunChapter, \
			ContentFactory::Fun, ContentFactory::Level1Content);
	m->addMenuItem(p);

	p = new Page((char *)"Sing");
	p->setChapterProperties(Chapter::FunChapter, \
			ContentFactory::Fun, ContentFactory::Level2Content);
	m->addMenuItem(p);

	p = new Page((char *)"Move");
	p->setChapterProperties(Chapter::FunChapter, \
			ContentFactory::Fun, ContentFactory::Level3Content);
	m->addMenuItem(p);
*/
}
