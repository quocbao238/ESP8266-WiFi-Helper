#include "wifi_helper_main.h"

EEPROMHelper EpromHelper;
WiFiModel wifiModel;
WiFiOledHelper wiFiOledHelper;
WiFiLedHelper wiFiLedHelper(LEDPIN);
WiFiButtonHelper wiFiButtonHelper(BUTTONPIN);
ESP8266WebServer server(80);

void debugLoop();
void runAP();
void runSTA();
bool initEppRomWiFiModel();
void loopLed();
void getWiFiModelByJson();
void loopCheckConnectNewDevice();

String softAppName = "wifihelper&";
String jsonDemo = "{\"ssid\": \"Welectronics_2.4ghz\",\"password\": \"TeamHshop\"}";
bool typeAP = false;
bool firstStart = true;

void mainSetup()
{
    DEBUG_PRINTLN(F("\n"));
    wiFiButtonHelper.begin();
    EpromHelper.begin();
    wiFiOledHelper.begin();
    wiFiLedHelper.begin();
    bool result = initEppRomWiFiModel();
    WiFi.mode(WIFI_AP_STA);
    result ? runSTA() : runAP();
}

void mainLoop()
{
    debugLoop();
    loopLed();
    loopCheckConnectNewDevice();
}

void runAP()
{
    typeAP = true;
    DEBUG_PRINTLN(F("   - WiFi Helper Run mode AP"));
    wiFiLedHelper.blink(1000, 100);
    String _strSoftAP = wifiModel.createRandomName(softAppName);
    DEBUG_PRINTLN("     - WiFi.softAP: " + String(_strSoftAP));
    WiFi.softAP(_strSoftAP);
    typeOled = showWiFiAddressType;
    wiFiOledHelper.showConnectWiFiSuccessful("Use app connect device");
}

// Kiểm tra có connect vào wifi được không?
bool onWaitConnectWiFi()
{
    bool _result = false;
    while (WiFi.status() != WL_CONNECTED)
    {
        wiFiLedHelper.blink(3000, 100);
        typeOled = loadingType;
        wiFiOledHelper.loadingProgressBar();
        bool _checkConfig = false;
        _checkConfig = wiFiButtonHelper.checkLongPress(7);
        if (_checkConfig == true)
        {
            DEBUG_PRINTLN(F("******* wiFiButtonHelper True *******"));
            _result = true;
            break;
        }
    }
    return _result;
}

void runSTA()
{
    DEBUG_PRINTLN(F("   - WiFi Helper Run mode STA"));
    WiFi.begin(wifiModel.getssId(), wifiModel.getPassword());
    // onWaitConnectWiFi --->   True -> RUN AP MODE
    //                   --->   False -> RUN STA
    if (onWaitConnectWiFi() == true)
    {
        runAP();
    }
    else
    {
        DEBUG_PRINT("IP address: ");
        DEBUG_PRINTLN(WiFi.localIP());
        typeOled = showWiFiAddressType;
        wiFiOledHelper.showConnectWiFiSuccessful(wifiModel.getssId());
    }
}

void debugLoop()
{
    if (firstStart)
    {
        // DEBUG_PRINTLN(F("******* mainLoop Run *******"));
        firstStart = false;
    }
}

void loopLed()
{
    if (typeAP)
        wiFiLedHelper.blink(1000, 100);
}

bool initEppRomWiFiModel()
{
    // DEBUG_PRINTLN("- Function initEppRomWiFiModel Start");

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

void loopCheckConnectNewDevice()
{   
    bool _checkConfig = false;
    _checkConfig = wiFiButtonHelper.checkLongPress(7);
    if (_checkConfig == true)
    {
        DEBUG_PRINTLN(F("******* wiFiButtonHelper True *******"));
        _checkConfig = false;
    }
}