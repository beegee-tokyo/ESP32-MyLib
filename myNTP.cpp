#include "myLib.h"

/** Structure to keep the local time */
struct tm timeinfo;

/**
 * Initialize NTP client
 * @return <code>bool</code>
 *		true if time was updated within 10 seconds
 */
bool initNTP() {
	configTzTime("UTC-8:00","0.asia.pool.ntp.org", "1.asia.pool.ntp.org", "2.asia.pool.ntp.org");
	if (getLocalTime(&timeinfo, 10000)) {  // wait up to 10sec to sync
		return true;
	}
	return false;
}

/**
 * Try to get time from NTP server
 * @return <code>bool</code>
 *		true if time was updated
 */
bool tryGetTime() {
	if (getLocalTime(&timeinfo, 0)) {  // don't wait for  sync
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
	time_t now;
	time(&now); // get time (as epoch)
	localtime_r(&now, &timeinfo); // update tm struct with current time

	// digital clock display of the time as string
	String dateTime = String(timeinfo.tm_hour) + ":";
	dateTime += getDigits(timeinfo.tm_min) + " ";
	dateTime += String(timeinfo.tm_mday) + ".";
	dateTime += String(timeinfo.tm_mon+1) + ".";
	dateTime += String(timeinfo.tm_year+1900);
	return dateTime;
}

/**
 * Generate a string with formatted time
 * @return <code>String</code>
 *			String with current time as hh:mm
 */
String digitalTimeDisplay() {
	time_t now;
	time(&now); // get time (as epoch)
	localtime_r(&now, &timeinfo); // update tm struct with current time

	// digital clock display of the time as string
	String dateTime = String(timeinfo.tm_hour) + ":";
	dateTime += getDigits(timeinfo.tm_min);
	return dateTime;
}

/**
 * Generate a string with formatted time
 * @return <code>String</code>
 *			String with current time as hh:mm:ss
 */
String digitalTimeDisplaySec() {
	time_t now;
	time(&now); // get time (as epoch)
	localtime_r(&now, &timeinfo); // update tm struct with current time

	// digital clock display of the time as string
	String dateTime = String(timeinfo.tm_hour) + ":";
	dateTime += getDigits(timeinfo.tm_min) + ":";
	dateTime += String(timeinfo.tm_sec);
	return dateTime;
}

/**
 * Generate a string with formatted date
 * @return <code>String</code>
 *			String with current date as dd.mm.yy
 */
String digitalDateDisplay() {
	time_t now;
	time(&now); // get time (as epoch)
	localtime_r(&now, &timeinfo); // update tm struct with current time

	// digital clock display of the time as string
	String dateTime = String(timeinfo.tm_mday) + ".";
	dateTime += getDigits(timeinfo.tm_mon+1) + ".";
	dateTime += String(timeinfo.tm_year+1900);
	return dateTime;
}
