/*
 * by Ozan Oner
 * PIR motion sensor library
 * http://www.cooking-hacks.com/pir-motion-sensor
 */

#ifndef _PIRMOTION_H_
#define _PIRMOTION_H_

#include <Arduino.h>

#define PIRM_SCAN_INTERVAL 2000

class PIRMotion {
public:
	PIRMotion(int port, uint8_t useInternalPullup); // constructor
	void update(); // monitor function
	void setMotionCallback(void (*callback)(void)); // motion callback
	void setLagAfterMotion(int secs); // to set a lag 
private:
	int port;
	unsigned long nextRead;
	unsigned long timeLag;
	void (*callback)(void);
};

#endif
