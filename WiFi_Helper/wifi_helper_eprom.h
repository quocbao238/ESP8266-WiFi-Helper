#ifndef _EEPROM_ESP_B_
#define _EEPROM_ESP_B_
#endif

#include "Arduino.h"
/*
   PIN  && VALUE
   EEPROM
*/


extern "C" {
  typedef void (*Warning_Function)();
}
class EEPROMHelper {
  public:
    Warning_Function pF_Warning;
    EEPROMHelper();
    void begin();
    void writeJsonWiFi(String jsonStr);
    String readJsonWiFi();
};

