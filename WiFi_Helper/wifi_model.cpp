#include "wifi_model.h"
#include "Arduino.h"
#include "wifi_helper_debug.h"

StaticJsonDocument<200> jsonDoc;

String WiFiModel::getToken()
{
	return token;
}
void WiFiModel::setToken(String _token)
{

	token = _token;
}

String WiFiModel::getssId()
{
	return ssId;
}
void WiFiModel::setssId(String _ssId)
{
	ssId = _ssId;
}

String WiFiModel::getPassword()
{
	return password;
}
void WiFiModel::setPassword(String _password)
{
	password = _password;
}

bool WiFiModel::initWiFiModel(String _jsonStr)
{	
	bool _result = readJson(_jsonStr);
	return _result;
}

bool WiFiModel::readJson(String _jsonStr)
{
	DeserializationError error = deserializeJson(jsonDoc, _jsonStr);
	if (error)
	{
		DEBUG_PRINTLN(F("deserializeJson() failed: "));
		DEBUG_PRINTLN(error.f_str());
		return false;
	}
	String _ssidRead = jsonDoc["ssid"];
	String _passRead = jsonDoc["password"];
	if (_ssidRead != "null" && _passRead != "null")
	{
		setssId(_ssidRead);
		setPassword(_passRead);
		DEBUG_PRINTLN("NewSSID:" + _ssidRead + " - NewPassword: " + _passRead);
		return true;
	}
	return false;
}
