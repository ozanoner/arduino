/*
 * by Ozan Oner
 * PIR motion sensor library
 * http://www.cooking-hacks.com/pir-motion-sensor
 */

#ifndef _PIRMOTION_H_
#define _PIRMOTION_H_

#include "Arduino.h"
#include "ClientOwner.h"
#include "PIRMotionClient.h"

// default value for scan interval
#define PIRM_SCAN_INTERVAL 2000

template<class T> class PIRMotion;

template<>
class PIRMotion<PIRMotionClient>: public ClientOwner<PIRMotionClient> {
public:
	PIRMotion(int pin, uint8_t useInternalPullup);
	// monitor function
	void update(); 
	void setLagAfterMotion(int secs) { this->timeLag = secs*1000L; };
	void setReportInterval(int secs) { this->reportInterval = secs*1000L; };
private:
	int pin;
	unsigned long reportInterval;
	unsigned long nextReport;
	// 0 for reporting disabled
	// 1 for reporting enabled
	// >= 2 motion
	int reportState;

	unsigned long nextRead;
	unsigned long timeLag;
	void informClients();
};

#endif
