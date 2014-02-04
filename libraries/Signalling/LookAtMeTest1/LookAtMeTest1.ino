
#include <SignalController.h>
#include <SignalPattern.h>
#include <LedSignalSource.h>
#include <BuzzerSignalSource.h>
#include <Timer.h>

#define PATTERN_PAT1 0

Timer timer;
SignalController *controller;
SignalPattern pat1(PATTERN_PAT1, &timer, pat1Start);
LedSignalSource ledSignal(13, 100, 1900);
BuzzerSignalSource buzzSignal(12, &timer, 100, 500);

void setup() {
  Serial.begin(9600);
	controller = SignalController::getInstance();
	controller->setPattern(PATTERN_PAT1, &pat1);
	pat1.addSignalSource(&ledSignal);
	pat1.addSignalSource(&buzzSignal);

	controller->startPattern(PATTERN_PAT1);
}

void loop() {
	timer.update();
	controller->update();
}

int pat1Start(void) {
	return timer.every(2000, pat1Trigger, 3);
}

void pat1Trigger(void) {
  Serial.println("pat1Trigger");
	pat1.trigger();
}
