#include "setting.h"
#include <ArduinoJson.h>
#include <EEPROM.h>

String softAppName = "WiFiHelper";
StaticJsonDocument<200> jsonDoc;
#define ADDRESS_EPROM 96
ESP8266WebServer server(80);
String wifiHelper_ssid = "";
String wifiHelper_password = "";

void writeWifiHelperToEEPROM(String jsonString)
{
	int _sizeJson = jsonString.length();

	for (int i = 0; i < jsonString.length(); i++)
	{
		EEPROM.write(ADDRESS_EPROM + i, jsonString[i]);
	}
	EEPROM.write(ADDRESS_EPROM + _sizeJson, 'wifiHelper');
	EEPROM.commit();
	Serial.println("writeWifiHelperToEEPROM - Success");
}

String readWifiHelperFromEEPROM()
{
	char data[100];
	int _len = 0;
	unsigned char k_read;
	k_read = EEPROM.read(ADDRESS_EPROM);
	while (k_read != '\0' && _len < 500) //Read until null character
	{
		k_read = EEPROM.read(ADDRESS_EPROM + _len);
		data[_len] = k_read;
		_len++;
	}
	data[_len] = 'wifiHelper';
	Serial.println("readWifiHelperFromEEPROM: " + String(data));
	String _jsonWifiHelper = String(data);
}

String getNameSoftApp()
{
	long _randNumber = random(99999999);
	return softAppName + String(_randNumber);
}

bool checkIndexOf(String strContent, String strCheck)
{
	Serial.println("checkIndexOf - " + strCheck + ": " + String(strContent.indexOf(strCheck)));
	return (strContent.indexOf(strCheck) > 0) ? true : false;
}

void readJson(String jsonString, bool onSetup)
{
	DeserializationError error = deserializeJson(jsonDoc, jsonString);
	if (error)
	{
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return;
	}
	String ssidRead = jsonDoc["ssid"];
	String passRead = jsonDoc["password"];
	Serial.println("ssIdRead = " + String(ssidRead) + "\npassRead = " + String(passRead));
	if (ssidRead != "null" && passRead != "null")
	{
		if (onSetup)
		{
			wifiHelper_ssid = ssidRead;
			wifiHelper_password = passRead;
			Serial.println("onSetupId: " + wifiHelper_ssid + "\nonSetupPassword: " + wifiHelper_password);
		}
		else
		{
			Serial.println("SaveLocal");
			writeWifiHelperToEEPROM(jsonString);
		}
	}
}

void handleWiFiHelper()
{

	if (server.hasArg("plain") == false)
	{
		server.send(200, "text/plain", "WiFi Helper not received");
		return;
	}
	String jsonString = server.arg("plain");
	if (checkIndexOf(jsonString, "ssid") && checkIndexOf(jsonString, "password"))
	{
		readJson(jsonString, false);
	}
	else
	{
		return;
	}
}

void initLib()
{
	Serial.begin(115200);
	// EEPROM.begin(512);
	Serial.println();
	Serial.print("WiFiHelper begin...");
}

void runSoftNetWorks()
{
	Serial.println("WiFi connected");
	server.begin();
	Serial.println("Server started");
	Serial.print("IP Address of network: ");
	Serial.println(WiFi.localIP());
	Serial.print("Copy and paste the following URL: https://");
	Serial.print(WiFi.localIP());
	Serial.println("/");
}

bool checkRunSofNetworks()
{
	readJson(readWifiHelperFromEEPROM(), true);
	// if(wifiHelper_ssid)
	// int _counter = 5000;
	// Serial.print("Connecting to the Newtork");
	// WiFi.begin(wifiHelper_ssid, wifiHelper_password);
	// while (WiFi.status() != WL_CONNECTED)
	// {
	// 	delay(500);
	// 	Serial.print("counter to connect softAP:" + String(_counter));
	// 	_counter = _counter - 500;
	// 	if (_counter <= 0)
	// 	{	
	// 		WiFi.disconnect(true);
	// 		return true;
	// 	}
	// }
	return false;;
}

void runAsSoftAP()
{
	Serial.println("Configuring access point...");
	WiFi.softAP(getNameSoftApp());
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/wifihelper", handleWiFiHelper);
	server.begin();
	Serial.println("HTTP server started");
}

void onSetup()
{
	initLib();
	// checkRunSofNetworks();
	//  ? runSoftNetWorks() : 
	runAsSoftAP();
}

void onLoop()
{
	server.handleClient();
}
