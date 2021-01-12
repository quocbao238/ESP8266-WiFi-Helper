#include "wifi_helper_main.h"

EEPROMHelper EpromHelper;
WiFiModel wifiModel;
WiFiOledHelper wiFiOledHelper;
WiFiLedHelper wiFiLedHelper(LEDPIN);
WiFiButtonHelper wiFiButtonHelper(BUTTONPIN);
ESP8266WebServer server(80);

long lastTimeReadSensor = 0;

void debugLoop();
void runAP();
void runSTA();
bool initEppRomWiFiModel();
void loopLed();
void getWiFiModelByJson();
void loopCheckConnectNewDevice();
void handelWiFiHelper();
void runHumiTempDemo();

String softAppName = "wifihelper&";
String jsonDemo = "{\"ssid\": \"Welectronics_2.4ghz\",\"password\": \"TeamHshop\"}";
bool typeAP = false;

void mainSetup()
{

    DEBUG_PRINTLN(F("\n"));
    wiFiButtonHelper.begin();
    EpromHelper.begin();
    wiFiOledHelper.begin();
    wiFiLedHelper.begin();
    wifiModel.setToken(EpromHelper.readToken());
    bool result = initEppRomWiFiModel();
    WiFi.mode(WIFI_AP_STA);
    runAP();
    if (result == true)
        runSTA();
}

void mainLoop()
{
    if (typeAP)
    {
        wiFiLedHelper.blink(1000, 100);
        server.handleClient();
        wiFiOledHelper.showConnectWiFiSuccessful("Use app connect device");
    }
    else
    {
        runHumiTempDemo();
        loopCheckConnectNewDevice();
    }
}

void runAP()
{
    typeAP = true;
    DEBUG_PRINTLN(F("   - WiFi Helper Run mode AP"));
    wiFiLedHelper.blink(1000, 100);
    String _strSoftAP = softAppName + wifiModel.getToken();
    DEBUG_PRINTLN("     - WiFi.softAP: " + String(_strSoftAP));
    WiFi.softAP(_strSoftAP);
    typeOled = showWiFiAddressType;
    wiFiOledHelper.showConnectWiFiSuccessful("Use app connect device");
    server.on("/wifihelper", handelWiFiHelper);
    server.begin(); //Start Server
}

void handelWiFiHelper()
{ //Handler for the body path

    if (server.hasArg("plain") == false)
    {
        server.send(200, "text/plain", "Body not received");
        return;
    }
    String _responseCallBack = server.arg("plain");
    DEBUG_PRINTLN(_responseCallBack);
    bool _result = wifiModel.readJson(_responseCallBack);
    if (_result == true)
    {
        server.send(200, "Successfully");
        EpromHelper.writeJsonWiFi(_responseCallBack);
        ESP.restart();
    }
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
    }
    else
    {
        DEBUG_PRINT("IP address: ");
        DEBUG_PRINTLN(WiFi.localIP());
        typeOled = showWiFiAddressType;
        typeAP = false;
        wiFiOledHelper.showConnectWiFiSuccessful(wifiModel.getssId());
        wiFiLedHelper.blinkOff();
    }
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
        EpromHelper.clearWiFiEEPRom();
        typeAP = true;
        _checkConfig = false;
    }
}

void runHumiTempDemo()
{
    if (millis() - lastTimeReadSensor > 3000)
    {
        lastTimeReadSensor = millis();
        double _randomTemp = random(20, 40);
        double _randomTemp2 = random(100);
        double _randomHumi = random(60, 90);
        double _randomHumi2 = random(100);
        double _temp = _randomTemp + _randomTemp2 / 100;
        double _humi = _randomHumi + _randomHumi2 / 100;
        DEBUG_PRINTLN("Temp:" + String(_temp));
        DEBUG_PRINTLN("Humi:" + String(_humi));
        wiFiOledHelper.showTempHumidity(String(_temp),String(_humi));
    }
}