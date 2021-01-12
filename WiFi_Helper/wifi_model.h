#ifndef WIFI__MODEL_H_
#define WIFI__MODEL_H_
#endif
#include "Arduino.h"
#include <ArduinoJson.h>

extern StaticJsonDocument<200> jsonDoc;

class WiFiModel
{
private:
    String ssId;
    String password;
    String token;
    String userToken;

public:
    String getToken();
    String getssId();
    String getPassword();
    String getUserToken();
    void setToken(String _totken);
    void setssId(String _ssId);
    void setPassword(String _password);
    void setUserToken(String userToken);
    bool initWiFiModel(String _jsonStr);
    bool readJson(String _jsonStr);
};
