#ifndef _WIFI_OLED_V2_
#define _WIFI_OLED_V2_
#endif

#include "Arduino.h"
#include "TimeLib.h"
#include "wifi_helper_debug.h"
#include <Wire.h>
#include "SSD1306Wire.h"

#define WiFi_Logo_width 60
#define WiFi_Logo_height 36

extern "C"
{
	typedef void (*Warning_Function)();
}
class WiFiOledHelper
{
public:
	Warning_Function pF_Warning;
	WiFiOledHelper();
	void begin();
	void showConnectWiFiSuccessful(String _ssid);
	void showTempHumidity(String temp, String humi);
	void loadingProgressBar();
};

enum typeShowOled
{
	loadingType,
	showWiFiAddressType
};

extern typeShowOled typeOled;
extern const uint8_t WiFi_Logo_bits[];
extern const uint8_t Irish_Grover_Regular_14[];
extern const uint8_t Irish_Grover_Regular_12[];