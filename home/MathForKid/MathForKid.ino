/*
 * by Vedat Ozan Oner
 * MathForKid.ino
 * 
 * An Arduino project for kids to study math 
 * and have some fun.
 *
 */


#include <Arduino.h>
#include <avr/pgmspace.h>

#include <MFK_Pins.h>
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

// hardware management
MFK_Hardware* hw;

// presentation
Menu* mainMenu;

void setup() {
	// for debugging purposes
	Serial.begin(9600);
  
	// get the instance and initialize it
	hw = MFK_Hardware::getInstance();
	hw->begin();

	// create user interface
	CreateUI();
	// show the main menu
	mainMenu->show();
    Serial.println(F("setup completed"));
}

void loop() {
	// update hardware
	hw->update();
	
	// update active visual item
	VisualItem *v = VisualItem::getActiveItem();
	if(v!=NULL)
		v->update();
}

void CreateUI() {
	mainMenu = new Menu("main");

	// addition
	Menu* m = new Menu("+");
	mainMenu->addMenuItem(m);

	// level-1 page
	Page* p = new Page("L1");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Addition, ContentFactory::Level1Content);
	m->addMenuItem(p);

	// level-2 page
	p = new Page("L2");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Addition, ContentFactory::Level2Content);
	m->addMenuItem(p);

/*
	// level-3 page
	p = new Page("L3");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Addition, ContentFactory::Level3Content);
	m->addMenuItem(p);

	// quiz page
	p = new Page("Q");
	p->setChapterProperties(Chapter::QuizChapter, \
			ContentFactory::Addition, ContentFactory::Level1Content);
	m->addMenuItem(p);

	// subtraction
	m = new Menu("-");
	mainMenu->addMenuItem(m);

	// level-1 page
	p = new Page("L1");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Subtraction, ContentFactory::Level1Content);
	m->addMenuItem(p);

	// level-2 page
	p = new Page("L2");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Subtraction, ContentFactory::Level2Content);
	m->addMenuItem(p);

	// level-3 page
	p = new Page("L3");
	p->setChapterProperties(Chapter::NormalChapter, \
			ContentFactory::Subtraction, ContentFactory::Level3Content);
	m->addMenuItem(p);

	// quiz page
	p = new Page("Q");
	p->setChapterProperties(Chapter::QuizChapter, \
			ContentFactory::Subtraction, ContentFactory::Level1Content);
	m->addMenuItem(p);
	
	// TODO: multiplication and division

	// fun
	m = new Menu("Fun");
	mainMenu->addMenuItem(m);

	// answer questions page
	p = new Page("Answer");
	p->setChapterProperties(Chapter::FunChapter, \
			ContentFactory::Fun, ContentFactory::Level1Content);
	m->addMenuItem(p);

	// sing a song page
	p = new Page("Sing");
	p->setChapterProperties(Chapter::FunChapter, \
			ContentFactory::Fun, ContentFactory::Level2Content);
	m->addMenuItem(p);

	// action page
	p = new Page("Move");
	p->setChapterProperties(Chapter::FunChapter, \
			ContentFactory::Fun, ContentFactory::Level3Content);
	m->addMenuItem(p);
*/
}
