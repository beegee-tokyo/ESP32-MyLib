#include "WiFi.h"
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FS.h>
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
