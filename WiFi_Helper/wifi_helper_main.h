#ifndef _WIFI_HELPER_MAIN_B_
#define _WIFI_HELPER_MAIN_B_
#endif

#include "Arduino.h"
#include "wifi_helper_eprom.h"
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "wifi_model.h"
#include "wifi_helper_oled_ver2.h"
#include "wifi_helper_led.h"
#include "wifi_helper_button.h"
#include "wifi_helper_define.h"
#include "wifi_helper_debug.h"

// extern ESP8266WebServer server(80);
extern String softAppName;
extern EEPROMHelper EpromHelper;
extern WiFiModel wifiModel;
extern WiFiOledHelper wiFiOledHelper;
extern WiFiLedHelper wiFiLedHelper;
extern WiFiButtonHelper wiFiButtonHelper;

extern void mainSetup();
extern void mainLoop();
