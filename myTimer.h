#ifndef mytimer_h
#define mytimer_h

#include <esp32-hal-timer.h>

typedef void (*callback_t)(void);

hw_timer_t *startTimer (uint64_t usTriggerTime, callback_t callback, bool repeat);
hw_timer_t *startTimerMsec (uint64_t msTriggerTime, callback_t callback, bool repeat);
hw_timer_t *startTimerSec (uint64_t sTriggerTime, callback_t callback, bool repeat);
void restartTimer(hw_timer_t *timerToRestart);
void stopTimer(hw_timer_t *timerToStop);
void stopAllTimers();
void IRAM_ATTR isrTimer0();
void IRAM_ATTR isrTimer1();
void IRAM_ATTR isrTimer2();
void IRAM_ATTR isrTimer3();

#endif
