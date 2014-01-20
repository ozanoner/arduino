/*
 * by Ozan Oner
 * SerialLcd implementation
 */

#include <SerialLcd.h>

SerialLcd::SerialLcd(Stream *serial) {
	this->serial = serial;
}

void SerialLcd::clr() {
	this->serial->write(SL_CMD_SPEC);
	this->serial->write(SL_CMD_CLR);
}

void SerialLcd::print(char *str) {
	this->serial->print(str);
}

void SerialLcd::println(char *str) {
	this->serial->print(str);
	this->serial->write(SL_CMD_LF);
}

void SerialLcd::setCursorPos(uint8_t pos) {
	this->serial->write(SL_CMD_SPEC);
	this->serial->write(SL_CMD_CURSOR_POS);
	this->serial->write(pos);
}

void SerialLcd::sendChar(uint8_t c) {
	this->serial->write(c);
}

void SerialLcd::setBacklight(uint8_t b) {
	this->serial->write(SL_CMD_BACKLIGHT);
	this->serial->write(b);
}

void SerialLcd::moveCursor(uint8_t direction) {
	switch(direction) {
		case SL_DIRECTION_LEFT:
			this->serial->write(SL_CMD_SPEC);
			this->serial->write(SL_CMD_MOVE_CURSOR_L);
			break;
		case SL_DIRECTION_RIGHT:
			this->serial->write(SL_CMD_SPEC);
			this->serial->write(SL_CMD_MOVE_CURSOR_R);
			break;
		default:
			break;
	}
}

void SerialLcd::showUnderlineCursor(uint8_t show) {
	this->serial->write(SL_CMD_SPEC);
	if(show)
		this->serial->write(SL_CMD_UCURSOR_ON);
	else
		this->serial->write(SL_CMD_UCURSOR_OFF);
}

void SerialLcd::showBlinkCursor(uint8_t show) {
	this->serial->write(SL_CMD_SPEC);
	if(show)
		this->serial->write(SL_CMD_BCURSOR_ON);
	else
		this->serial->write(SL_CMD_BCURSOR_OFF);
}

void SerialLcd::scrollScreen(uint8_t direction) {
	switch(direction) {
		case SL_DIRECTION_LEFT:
			this->serial->write(SL_CMD_SPEC);
			this->serial->write(SL_CMD_SCROLL_L);
			break;
		case SL_DIRECTION_RIGHT:
			this->serial->write(SL_CMD_SPEC);
			this->serial->write(SL_CMD_SCROLL_R);
			break;
		default:
			break;
	}
}

void SerialLcd::displayOn(uint8_t on) {
	this->serial->write(SL_CMD_SPEC);
	if(on) 
		this->serial->write(SL_CMD_DISP_ON);
	else 
		this->serial->write(SL_CMD_DISP_OFF);
}

void SerialLcd::toggleSplash() {
	this->serial->write(SL_CMD_SPEC);
	this->serial->write(SL_CMD_SPLASH_TOGGLE);
}
