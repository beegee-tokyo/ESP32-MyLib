# ESP32-MyLib    
Here I collect functions that I am using in all my ESP32 projects.
It is work in progress and will be updated over time.

# Available libraries    
## bgConnect    
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

**`bool connWiFiManager(const char *ssid, uint32_t connTimeout, uint32_t portalTimeout, bool connAuto)`**
Tries to connect to the last known AP. If this fails or if there is no AP credentials stored the module switches into AP mode and a configuration portal is created to setup the network credentials    
* **`ssid`**　SSID for the AP in case the connection fails    
* **`connTimeout`**　Time to wait for connection to succeed    
* **`portalTimeout`**　Time to wait for input on configuration portal    
* **`connAuto`**　If true, the functions tries first to connect to an known AP    
            If false, the configuration portal is immediately opened    

**`bool connSmartConfig(uint32_t confTimeout, uint32_t connTimeout)`**    
Connect with SmartConfig. First try auto connect, if it fails wait for SmartConfig to get WiFI credentials from an Android or IPhone app.        
* **`confTimeout`** Time to wait to receive smart configuration    
* **`connTimeout`** Time to wait for connection to WiFi after configuration was received    
