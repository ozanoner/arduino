/*
 * by Ozan Oner
 * Serial LCD driver for
 * https://www.sparkfun.com/tutorials/289
 * See:
 * https://github.com/jimblom/Serial-LCD-Kit/wiki/Serial-Enabled-LCD-Kit-Datasheet
 */


#ifndef _SERIAL_LCD_H_
#define _SERIAL_LCD_H_


#define SL_DIRECTION_LEFT 0
#define SL_DIRECTION_RIGHT 1

#define SL_CMD_CR 0x0D
#define SL_CMD_LF 0x0A
#define SL_CMD_BCK 0x08

#define SL_CMD_BACKLIGHT 0x80

#define SL_CMD_SPEC 0xFE
#define SL_CMD_CLR 0x01
#define SL_CMD_MOVE_CURSOR_R 0x14
#define SL_CMD_MOVE_CURSOR_L 0x10
#define SL_CMD_SCROLL_R 0x1C
#define SL_CMD_SCROLL_L 0x18
#define SL_CMD_DISP_OFF 0x08
#define SL_CMD_DISP_ON 0x0C
#define SL_CMD_UCURSOR_ON 0x0E
#define SL_CMD_UCURSOR_OFF 0x0C
#define SL_CMD_BCURSOR_ON 0x0D
#define SL_CMD_BCURSOR_OFF 0x0C
#define SL_CMD_CURSOR_POS 0x80
#define SL_CMD_SPLASH_TOGGLE 0x1E


#include <Arduino.h>

class SerialLcd {
public:
	SerialLcd(Stream *serial);

	void clr(); // clear screen
	void print(char *str); // prints to current pos
	void println(char *str);
	
	// pos: 0..(max chars-1)
	void setCursorPos(uint8_t pos);
	// any char but especially [SL_CMD_CR|SL_CMD_LF|SL_CMD_BCK]
	// see https://www.sparkfun.com/datasheets/LCD/GDM1602K-Extended.pdf
	// for extended charset
	void sendChar(uint8_t c); 
	// backlight: 0-255
	void setBacklight(uint8_t b); 
	// direction: [SL_DIRECTION_LEFT|SL_DIRECTION_RIGHT]
	void moveCursor(uint8_t direction); 
	// show if !=0
	void showUnderlineCursor(uint8_t show);
	// show if !=0
	void showBlinkCursor(uint8_t show);
	// direction: [SL_DIRECTION_LEFT|SL_DIRECTION_RIGHT]
	void scrollScreen(uint8_t direction);
	// on if !=0
	void displayOn(uint8_t on);
	// toggle splash screen display. 
	// on if off, off if on
	void toggleSplash();
private:
	Stream *serial; // needs initialized out of the class
};

#endif
