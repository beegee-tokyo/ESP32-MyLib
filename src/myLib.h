#ifndef mylib_h
#define mylib_h

/**********************************************************/
// For myConnect
/**********************************************************/
#include "WiFi.h"
#include <ESPmDNS.h>
#include "WiFiUdp.h"
#include "ArduinoOTA.h"
#include "FS.h"
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

/** Connect to WiFi with defined method */
void createName(char *apName, int apIndex);

/** Connect with predefined SSID and password */
bool connDirect(const char *ssid, const char *password, uint32_t timeout);
/** Connect with WiFiManager */
bool connWiFiManager(const char *ssid, uint32_t connTimeout, uint32_t portalTimeout, bool connAuto);
/** Connect with SmartConfig */
bool connSmartConfig(uint32_t confTimeout, uint32_t connTimeout);

/**********************************************************/
// For myNTP
/**********************************************************/
// #include <NTPClient.h>
// #include <TimeLib.h>
// #include <WiFiUDP.h>

/** WiFiUDP class for NTP server */
extern WiFiUDP ntpUDP;

bool initNTP();
bool tryGetTime();
String digitalClockDisplay();
String digitalTimeDisplay();
String digitalTimeDisplaySec();
String digitalDateDisplay();

/**********************************************************/
// For myTimer
/**********************************************************/
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
