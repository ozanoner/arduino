#include <inttypes.h>
#include <SoftwareSerial.h>

#include "CLcd.h"
#include "C3But.h"
#include "Timer.h"

// arduino pins
const int LCD_RX=3;
const int LCD_TX=4;
const int BUT1=5;
const int BUT2=6;
const int BUT3=7;
const int LEDPIN=13;

// timeout values
unsigned long SMS4_TIMEOUT = 30*1000;
unsigned long SEC10 = 10L*1000;
unsigned long SEC5 = 5L*1000;
unsigned long WAKEUP_TIMEOUT = 60L*1000;


// buffers' size
#define LCD_DISP_SIZE 32
#define LCD_SECOND_LINE 16

char lcdDisp[LCD_DISP_SIZE];

CLcd lcd(LCD_RX, LCD_TX);
C3But btn(BUT1, BUT2, BUT3);
Timer timer;

int timerHandle=-1;


void setup() {
  lcd.initialize();
  btn.initialize();

  btn.setPressCallback(btnPressed);
  btn.setTwoPressCallback(twoBtnPressed);

  lcd.clr();

  lcdPrintError("Error test deneme 2 3 4 5 6 7 8 9 10 11");
  delay(3000);
  
  lcdPrintCoor(32.123123, 38.345456);
  delay(3000);

  lcdPrint("Initialized.", 0, 1);
}

void loop() {
  btn.update();
  timer.update();
}

void btnPressed(int b1) {
  char mess[20];
  memset(mess, 0, 20);
  sprintf(mess, "Button: %d", b1);
  lcdPrint(mess, 0, 1);
}


void twoBtnPressed(int b1, int b2) {
  if(timerHandle>=0) {
    timer.stop(timerHandle);
    timerHandle=-1;
    lcdPrint("TIMER STOPPED", LCD_SECOND_LINE, 0);
  }
  else {
    timerHandle = timer.every(SMS4_TIMEOUT, timerSms4TimeoutCallback);
    lcdPrint("TIMER STARTED", LCD_SECOND_LINE, 0);
  }
}

void timerSms4TimeoutCallback() {
  lcdPrint("TIMER TIMEOUT", LCD_SECOND_LINE, 0);
}


void lcdPrint(char *mess, uint8_t pos, uint8_t clr) {
  if(clr)	
    lcd.clr();
  lcd.setCursor(pos);
  lcd.print(mess);
}

void lcdPrintError(char *mess) {
  memset(lcdDisp, 0, LCD_DISP_SIZE);
  int maxMessSize = LCD_DISP_SIZE-5;
  if(strlen(mess)>maxMessSize)
    mess[maxMessSize]=0;
  sprintf(lcdDisp, "Err: %s", mess);
  lcdPrint(lcdDisp, 0, 1);
}

void lcdPrintCoor(float n, float e) {
  memset(lcdDisp, 0, LCD_DISP_SIZE);
  sprintf(lcdDisp, "N: %d.%d", (int)n, (long)((n-(int)n)*10000));
  lcdPrint(lcdDisp, 0, 1);
  memset(lcdDisp, 0, LCD_DISP_SIZE);
  sprintf(lcdDisp, "E: %d.%d", (int)e, (long)((e-(int)e)*10000));
  lcdPrint(lcdDisp, LCD_SECOND_LINE, 0);
}

