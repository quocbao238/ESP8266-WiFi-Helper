#ifndef _WIFI_HELPER_MAIN_B_
#define _WIFI_HELPER_MAIN_B_
#endif
#include "wifi_helper_eprom.h"
#include "wifi_model.h"
#include "Arduino.h"
#include "wifi_helper_debug.h"
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// extern ESP8266WebServer server(80);
extern String softAppName;
extern EEPROMHelper EpromHelper;
extern WiFiModel wifiModel;
extern void mainSetup();
extern void mainLoop();

