#include "wifi_helper_eprom.h"
#include "wifi_helper_debug.h"
#include <EEPROM.h>
#define ADDRESS_LENGH 500
#define ADDRESS_TOKEN 399

EEPROMHelper::EEPROMHelper() {}
void EEPROMHelper::begin()
{
  EEPROM.begin(512);
}

void EEPROMHelper::clearWiFiEEPRom()
{
  int _length = EEPROM.read(ADDRESS_LENGH);
  String _jsonStr = "";
  for (int i = 0; i < _length; i++)
  { EEPROM.write(i, 0); }
  EEPROM.commit();
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
  // EEPROM.end();
  DEBUG_PRINTLN();
  DEBUG_PRINTLN(F("   -------Write JsonWiFi Compile-------"));
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

String EEPROMHelper::readToken()
{
  String _jsonStr = "";
  for (int i = 0; i < 10; i++)
  {
    int address = ADDRESS_TOKEN + i;
    _jsonStr += char(EEPROM.read(address));
    delay(100);
  }
  _jsonStr.trim();
  DEBUG_PRINTLN();
  DEBUG_PRINTLN("TokenDevice:" + _jsonStr);
  return _jsonStr;
}

void EEPROMHelper::createToken()
{
  //  Clear EPROM
  // for (int i = ADDRESS_TOKEN; i < (ADDRESS_TOKEN + 10); i++)
  // {
  //   EEPROM.write(i, 0);
  // }
  // DEBUG_PRINTLN("CreateToken");

  long randomToken = random(9999999999);
  String _myToken = String(randomToken);
  DEBUG_PRINTLN(F("token Write: "));
  for (int i = 0; i < 10; i++)
  {
    int address = i + ADDRESS_TOKEN;
    EEPROM.write(address, _myToken[i]);
    delay(100);
    DEBUG_PRINT(_myToken[i]);
  }
  EEPROM.commit();
  // EEPROM.end();
  DEBUG_PRINTLN();
  DEBUG_PRINTLN("CreateTokenSucess");
}
