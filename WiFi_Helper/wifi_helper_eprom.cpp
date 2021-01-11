#include "wifi_helper_eprom.h"
#include "wifi_helper_debug.h"
#include <EEPROM.h>
#define ADDRESS_LENGH 500

EEPROMHelper::EEPROMHelper() {}
void EEPROMHelper::begin()
{
  EEPROM.begin(512);
  // DEBUG_PRINTLN(F("   -------Start EEPROMHelper-------"));
}

void EEPROMHelper::writeJsonWiFi(String _jsonStr)
{
  _jsonStr.trim();
  int _value = _jsonStr.length();

  // DEBUG_PRINTLN(F("   -------writeJsonWiFi Start-------"));
  //  Clear EPROM
  for (int i = 0; i < _value; i++)
  {
    EEPROM.write(i, 0);
  }

  EEPROM.write(ADDRESS_LENGH, _value);

  DEBUG_PRINTLN(F("writeJsonWiFi Write: "));
  for (int i = 0; i < _value; i++)
  {
    EEPROM.write(i, _jsonStr[i]);
    delay(50);
    DEBUG_PRINT(_jsonStr[i]);
  }
  EEPROM.commit();
  EEPROM.end();
  DEBUG_PRINTLN();
  // DEBUG_PRINTLN(F("   -------Write JsonWiFi Compile-------"));
}

String EEPROMHelper::readJsonWiFi()
{
  // DEBUG_PRINTLN(F("   -------readJsonWiFi Start-------"));

  int _length = EEPROM.read(ADDRESS_LENGH);

  String _jsonStr = "";
  for (int i = 0; i < _length; i++)
  {
    _jsonStr += char(EEPROM.read(i));
  }
  _jsonStr.trim();
  // DEBUG_PRINTLN("     + readJsonWiFi Result: " + String(_jsonStr.c_str()));
  // DEBUG_PRINTLN(F("   -------readJsonWiFi End-------"));

  return _jsonStr.c_str();
}
