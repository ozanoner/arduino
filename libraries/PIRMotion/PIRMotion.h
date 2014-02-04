/*
 * by Ozan Oner
 * PIR motion sensor library
 * http://www.cooking-hacks.com/pir-motion-sensor
 */

#ifndef _PIRMOTION_H_
#define _PIRMOTION_H_

#include <Arduino.h>
#include "ClientOwner.h"
#include "PIRMotionClient.h"

#define PIRM_SCAN_INTERVAL 2000

// template declaration
template<class T> class PIRMotion;


// specialized for PIRMotionClient
template<>
class PIRMotion<PIRMotionClient>: public ClientOwner<PIRMotionClient> {
public:
	PIRMotion(int port, uint8_t useInternalPullup); // constructor
	void update(); // monitor function
	void setLagAfterMotion(int secs); // to set a lag 
private:
	int port;
	unsigned long nextRead;
	unsigned long timeLag;
	void informClients();
};

#endif
