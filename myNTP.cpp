#include "myNTP.h"

/** WiFiUDP class for NTP server */
WiFiUDP ntpUDP;
/** NTP client class */
NTPClient timeClient(ntpUDP);

/**
 * Initialize NTP client
 */
void initNTP() {
	// Start NTP listener
	timeClient.begin();
	// Set timezone (PH +8h)
	timeClient.setTimeOffset(28800);
	// Force update of time from NTP server
	timeClient.forceUpdate();
}

/**
 * Try to get time from NTP server
 * @return <code>bool</code>
 *		true if time was updated
 */
bool tryGetTime() {
	if (timeClient.update()) {
		setTime(timeClient.getEpochTime());
		return true;
	}
	return false;
}

/**
 * Generate a string from a integer with leading zero if integer is smaller than 10
 * @param int
 *			Integer to be converted
 * @return <code>String</code>
 *			Integer as String
 */
String getDigits(int digits) {
	if (digits < 10) {
		return "0" + String(digits);
	} else {
		return String(digits);
	}
}

/**
 * Generate a string with formatted time and date
 * @return <code>String</code>
 *			String with current time as hh:mm dd.mm.yy
 */
String digitalClockDisplay() {
	// digital clock display of the time as string
	String dateTime = String(hour()) + ":";
	dateTime += getDigits(minute()) + " ";
	dateTime += String(day()) + ".";
	dateTime += String(month()) + ".";
	dateTime += String(year());
	return dateTime;
}

/**
 * Generate a string with formatted time
 * @return <code>String</code>
 *			String with current time as hh:mm
 */
String digitalTimeDisplay() {
	// digital clock display of the time as string
	String dateTime = String(hour()) + ":";
	dateTime += getDigits(minute());
	return dateTime;
}

/**
 * Generate a string with formatted time
 * @return <code>String</code>
 *			String with current time as hh:mm:ss
 */
String digitalTimeDisplaySec() {
	// digital clock display of the time as string
	String dateTime = String(hour()) + ":";
	dateTime += getDigits(minute()) + ":";
	dateTime += getDigits(second());
	return dateTime;
}

/**
 * Generate a string with formatted date
 * @return <code>String</code>
 *			String with current time as dd.mm.yy
 */
String digitalDateDisplay() {
	// digital clock display of the time as string
	String dateTime = String(day()) + ".";
	dateTime += String(month()) + ".";
	dateTime += String(year());
	return dateTime;
}
