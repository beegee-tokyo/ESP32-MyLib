#include "myLib.h"

/**
 * Create Access Point name & mDNS name
 * from MAC address
 *
 * Created name is stored in the global char *apName[]
 **/
void createName(char *apName, int apIndex) {
	uint8_t baseMac[6];
	// Get MAC address for WiFi station
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	char baseMacChr[18] = {0};
	sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);

	apName[apIndex] = baseMacChr[0];
	apName[apIndex+1] = baseMacChr[1];
	apName[apIndex+2] = baseMacChr[9];
	apName[apIndex+3] = baseMacChr[10];
	apName[apIndex+4] = baseMacChr[12];
	apName[apIndex+5] = baseMacChr[13];
	apName[apIndex+6] = baseMacChr[15];
	apName[apIndex+7] = baseMacChr[16];
}

/**
 * Connect to WiFi with defined method
 *
/**
 * Connect with predefined SSID and password
 *
 * @param ssid
 *				SSID to connect to
 * @param password
 *				Password for this AP
 * @param timeout
 *				Time to wait for connection to succeed
 * @return <code>boolean</code>
 *				True if connection successfull
 *				False if connection failed after
 */
bool connDirect(const char *ssid, const char *password, uint32_t timeout) {
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	uint32_t startTime = millis();
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		if (millis()-startTime > timeout) { // check if waiting time exceeded
			return false;
		}
	}
	return true;
}

/**
 * Connect with WiFiManager
 * depending on autoConn parameter tries
 * first try auto connect, if it fails
 * open configuration portal
 * or just opens configuration portal
 *
 * @param ssid
 *				SSID for the AP in case the connection fails
 * @param connTimeout
 *				Time to wait for connection to succeed
 * @param portalTimeout
 *				Time to wait for input on configuration portal
 *				if 0 then ESP stays in config portal mode,
 *				no return from this function until reset or configurated
 * @param connAuto
 *				If true,
 * @return <code>boolean</code>
 *				True if connection successfull
 *				False if connection failed after connTimeout ms
 *				or config portal timeout occured
 */
bool connWiFiManager(const char *ssid, uint32_t connTimeout, uint32_t portalTimeout, bool connAuto) {
	//Local intialization. Once its business is done, there is no need to keep it around
	WiFiManager wifiManager;
	uint32_t startTime = millis();
	if (connAuto) {
		// Set a connection timeout of connTimeout seconds before opening the configuration portal
		wifiManager.setConfigPortalTimeout(connTimeout);
		if (!wifiManager.autoConnect(ssid)) {
			Serial.println("Could not connect to network, restart Config Portal");
		 	wifiManager.setConfigPortalTimeout(portalTimeout);
		 	wifiManager.startConfigPortal(ssid);
			return false;
		}
	} else {
		// Set a connection timeout before closing the configuration portal
		wifiManager.setConfigPortalTimeout(portalTimeout);
		wifiManager.startConfigPortal(ssid);
		//Wait for SmartConfig packet from mobile
		while (WiFi.waitForConnectResult() != WL_CONNECTED) {
			if (connTimeout != 0) {
				if (millis()-startTime > connTimeout) { // check if waiting time exceeded
					return false;
				}
			}
		}
	}
	return true;
}

/**
 * Connect with SmartConfig
 * First try auto connect, if it fails
 * open configuration portal
 *
 * @param confTimeout
 *				Time to wait to receive smart configuration
 *				if 0 it will wait forever
 * @param connTimeout
 *				Time to wait for connection to WiFi after
 *				configuration was received
 * @return <code>boolean</code>
 *				True if configuration and connection successfull
 *				False if timeout
 */
bool connSmartConfig(uint32_t confTimeout, uint32_t connTimeout) {
	uint32_t startTime = millis();
	//Init WiFi as Station, start SmartConfig
	WiFi.mode(WIFI_AP_STA);
	WiFi.beginSmartConfig();
	//Wait for SmartConfig packet from mobile
	while (!WiFi.smartConfigDone()) {
		if (confTimeout != 0) {
			if (millis()-startTime > confTimeout) { // check if waiting time exceeded
				return false;
			}
		}
	}
	//Wait for WiFi to connect to AP
	startTime = millis();
	while (WiFi.status() != WL_CONNECTED) {
		if (connTimeout != 0) {
			if (millis()-startTime > connTimeout) { // check if waiting time exceeded
				return false;
			}
		}
	}
	return true;
}
