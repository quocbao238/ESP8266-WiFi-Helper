#include "wifi_helper_main.h"

EEPROMHelper EpromHelper;
WiFiModel wifiModel;
ESP8266WebServer server(80);

void debugLoop();
bool initEppRomWiFiModel();
void getWiFiModelByJson();

String softAppName = "WiFiHelper";
String jsonDemo = "{\"ssid\": \"Welectronics_2.4ghz\",\"password\": \"TeamHshop\"}";
bool firstStart = true;

void mainSetup()
{
    DEBUG_PRINTLN(F("\n"));
    DEBUG_PRINTLN(F("******* mainSetup Start *******"));
    bool result = initEppRomWiFiModel();
    if (result)
    {
        DEBUG_PRINTLN(F("   - WiFi Helper Run mode STA"));
    }
    else
    {
        DEBUG_PRINTLN(F("   - WiFi Helper Run mode AP"));
    }
    DEBUG_PRINTLN(F("******* mainSetup End *******"));
}

void mainLoop() { debugLoop(); }

void debugLoop()
{
    if (firstStart)
    {
        DEBUG_PRINTLN(F("******* mainLoop Run *******"));
        firstStart = false;
    }
}

bool initEppRomWiFiModel()
{
    // DEBUG_PRINTLN("- Function initEppRomWiFiModel Start");
    EpromHelper.begin();
    String jsonStr = EpromHelper.readJsonWiFi();
    if (jsonStr.length() > 0)
    {
        bool _result = wifiModel.initWiFiModel(jsonStr);
        if (_result)
        {
            DEBUG_PRINTLN("   - Ssid:" + String(wifiModel.getssId()));
            DEBUG_PRINTLN("   - Password:" + String(wifiModel.getPassword()));
            // DEBUG_PRINTLN("- Function initEppRomWiFiModel Successfully");
            return true;
        }
        else
        {

            return false;
        }
    }
    else
    {
        return false;
        DEBUG_PRINTLN("   - Function initEppRomWiFiModel Fail");
    }
}
