#ifndef timer_h
#define timer_h

#include <esp32-hal-timer.h>

extern bool timerInUse[];
extern hw_timer_t *attachedTimer[];

typedef void (*callback_t)(void);

hw_timer_t *startTimer (uint64_t repeatTime, callback_t callback, bool repeat);
hw_timer_t *startTimerMsec (uint64_t repeatTime, callback_t callback, bool repeat);
hw_timer_t *startTimerSec (uint64_t repeatTime, callback_t callback, bool repeat);
void stopTimer(hw_timer_t *timerToStop);
void stopAllTimers();

#endif
