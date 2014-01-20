
#include <SignalController.h>
#include <SignalPattern.h>
#include <LedSignalSource.h>
#include <BuzzerSignalSource.h>
#include <Timer.h>

#define PATTERN_PAT1 0

Timer timer;
SignalController *controller;
SignalPattern pat1(&timer, pat1Start);
LedSignalSource ledSignal(3, 0, 1000);
BuzzerSignalSource buzzSignal(4, &timer, 500, 1500);

void setup() {
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
	pat1.trigger();
}
