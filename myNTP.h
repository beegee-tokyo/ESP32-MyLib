#ifndef myntp_h
#define myntp_h

#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiUDP.h>

/** WiFiUDP class for NTP server */
extern WiFiUDP ntpUDP;
/** NTP client class */
extern NTPClient timeClient;

void initNTP();
bool tryGetTime();
String digitalClockDisplay();
String digitalTimeDisplay();
String digitalTimeDisplaySec();
String digitalDateDisplay();

#endif
