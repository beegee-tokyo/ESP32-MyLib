#include "myTimer.h"

int availTimers = 4;
bool timerInUse[4] = {false, false, false, false};
hw_timer_t *attachedTimer[4] = {NULL, NULL, NULL, NULL};

/**
	startTimerMsec
	Start a hardware timer with repeat time in milliseconds
*/
hw_timer_t *startTimerMsec (uint64_t repeatTime, callback_t callback, bool repeat) {
	return startTimer (repeatTime*1000, callback, repeat);
}

/**
	startTimerSec
	Start a hardware timer with repeat time in seconds
*/
hw_timer_t *startTimerSec (uint64_t repeatTime, callback_t callback, bool repeat) {
	return startTimer (repeatTime*1000*1000, callback, repeat);
}

/**
	startTimer
	Start a hardware timer with repeat time in microseconds
*/
hw_timer_t *startTimer (uint64_t repeatTime, callback_t callback, bool repeat) {
	// Find free timer
	uint8_t timerToUse;
	for (timerToUse = 0; timerToUse < availTimers; timerToUse++) {
		if (timerInUse[timerToUse] == false) {
			break;
		}
	}
	if (timerToUse == availTimers) {
		// No free timer found!
		return NULL;
	}
  // Use timerNum timer of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  attachedTimer[timerToUse] = timerBegin(timerToUse, 80, true);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(attachedTimer[timerToUse], callback, true);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(attachedTimer[timerToUse], repeatTime, repeat);

  // Start an alarm
  timerAlarmEnable(attachedTimer[timerToUse]);
	timerInUse[timerToUse] = true;
	return attachedTimer[timerToUse];
}

/**
	stopTimer
	Stop a hardware timer
*/
void stopTimer(hw_timer_t *timerToStop) {
	uint8_t timerUsed;
	for (timerUsed = 0; timerUsed < availTimers; timerUsed++) {
		if (attachedTimer[timerUsed] == timerToStop) {
			timerEnd(timerToStop);
			attachedTimer[timerUsed] = NULL;
			timerInUse[timerUsed] = false;
			break;
		}
	}
}

/**
	stopAllTimer
	Stop a all running timers
*/
void stopAllTimers() {
	uint8_t timerUsed;
	for (timerUsed = 0; timerUsed < availTimers; timerUsed++) {
		if (attachedTimer[timerUsed] != NULL) {
			timerEnd(attachedTimer[timerUsed]);
			attachedTimer[timerUsed] = NULL;
			timerInUse[timerUsed] = false;
		}
	}
}
