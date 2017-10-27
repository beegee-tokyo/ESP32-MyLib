# ESP32-MyLib    
Here I collect functions that I am using in all my ESP32 projects.
It is work in progress and will be updated over time.

# Available libraries    
## myConnect    
WiFi connection functionalities    

### Create Access Point name & mDNS name from MAC address
**`void createName(char *apName, int apIndex)`**    
Generates an unique name for the module from a given prefix and the first and last 3 parts of the MAC address of the module.    
* **`apName`** points to a character array that contains the prefix and placeholders for the unique id. I am using <hardware>-<module type>-xxxxxxxx. For my tests this is `ESP32-Test-xxxxxx`.    
* **`apIndex`** is the index of the first placeholder where the MAC address ID will be inserted.    

### Connect to WiFi with defined method    
**`bool connDirect(const char *ssid, const char *password, uint32_t timeout)`**    
Tries to connect to a known AP within a given timeout.    
* **`ssid`** is the SSID to connect to    
* **`password`** is the password for the AP    
* **`timeout`** is the time in milli seconds to wait for the connection    
* **`return`** flag if connection was successfull    

**`bool connWiFiManager(const char *ssid, uint32_t connTimeout, uint32_t portalTimeout, bool connAuto)`**
Tries to connect to the last known AP. If this fails or if there is no AP credentials stored the module switches into AP mode and a configuration portal is created to setup the network credentials    
* **`ssid`**　SSID for the AP in case the connection fails    
* **`connTimeout`**　Time to wait for connection to succeed    
* **`portalTimeout`**　Time to wait for input on configuration portal    
* **`connAuto`**　If true, the functions tries first to connect to an known AP    
            If false, the configuration portal is immediately opened    
* **`return`** flag if connection was successfull    

**`bool connSmartConfig(uint32_t confTimeout, uint32_t connTimeout)`**    
Connect with SmartConfig. First try auto connect, if it fails wait for SmartConfig to get WiFI credentials from an Android or IPhone app.        
* **`confTimeout`** Time to wait to receive smart configuration    
* **`connTimeout`** Time to wait for connection to WiFi after configuration was received    
* **`return`** flag if connection was successfull    

## myTimer    
ESP32 HW timer functionalities    
4 HW timers are available and can be used with this library

### Start timer
**`hw_timer_t *startTimerMsec (uint64_t triggerTime, callback_t callback, bool repeat)`**    
**`hw_timer_t *startTimerSec (uint64_t triggerTime, callback_t callback, bool repeat)`**    
**`hw_timer_t *startTimer (uint64_t triggerTime, callback_t callback, bool repeat)`**    
Start a timer for a single (repeat = false) or repeating (repeat = true) trigger.    
startTimerSec for use with seconds,
startTimerMSec for use with milli seconds,
startTimer for use with micro seconds    
* **`triggerTime`** time to trigger in seconds, milli seconds or micro seconds    
* **`callback`** the function to be called when the timer is triggered    
* **`repeat`** flag if the timer will be triggered repeatedly or only one time
* **`return`** pointer to timer structure, needed to stop the timer    

### Restart a specific timer    
**`void restartTimer(hw_timer_t *timerToRestart)`**    
Restarts a timer with the same repeat/alarm time as it was created   
* **`timerToRestart`** timer to be restarted    

### Stop a specific timer
**`void stopTimer(hw_timer_t *timerToStop)`**    
Stop the timer associated with timerToStop timer structure    
* **`timerToStop`** timer to be stopped    

### Stop all timers
**`void stopAllTimers()`**    
Stop all used timers, usefull to stop timer triggered repeating events when an OTA starts    

## myNTP    
NTP client wrapper for NTPClient by Fabrice Weinberg ==> [NTPClient](https://github.com/arduino-libraries/NTPClient)    

### Init NTP client
**`void initNTP()`**    
Starts NTP client, sets timezone to Philippines (fix at the moment) and requests a first time update from the NTP server.    

### Get time from NTP server    
**`bool tryGetTime()`**    
calls NTP client update() to check if an updated time stamp is available   
* **`return`** true if update was available, false if error occured    

### Get time and date as String
**`String digitalClockDisplay()`**    
Returns time and date as string in the format hh:mm dd.mm.yy    
* **`return`** String with time and date readable     

### Get time as String
**`String digitalTimeDisplay()`**    
Returns time as string in the format hh:mm    
* **`return`** String with time readable     

### Get time as String with seconds
**`String digitalTimeDisplaySec()`**    
Returns time as string in the format hh:mm:ss    
* **`return`** String with time readable     

### Get time as String with seconds
**`String digitalTimeDisplaySec()`**    
Returns time as string in the format hh:mm:ss    
* **`return`** String with time readable     
