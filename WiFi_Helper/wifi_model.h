#ifndef WIFI__MODEL_H_
#define WIFI__MODEL_H_
#endif
#include "Arduino.h"
#include <ArduinoJson.h>


extern StaticJsonDocument<200> jsonDoc;

class WiFiModel {
private:
	String ssId;
	String password;
public:
	String getssId();
    String getPassword();
    void setssId(String _ssId);
    void setPassword(String _password);
    bool initWiFiModel(String _jsonStr);
    bool readJson(String _jsonStr);
};
