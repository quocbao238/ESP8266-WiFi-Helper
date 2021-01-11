
#ifndef __WIFI_LED_HELPER_H__
#define __WIFI_LED_HELPER_H__

#include <Arduino.h>

enum blink_t {BLINK_ON, BLINK_OFF};

class WiFiLedHelper {
  private:
    unsigned long m_blinkTime;
    int m_onForTime;
    int m_offForTime;
    blink_t m_blinkState;
    short m_pin;
    int m_resolution;

    void reset();

  public:

    WiFiLedHelper(int pin);
    void begin();
    void blink(int on_for, int off_for);
    void blink();
    void setOnTime(int ms);
    void setOffTime(int ms);
    void setBlinkState(blink_t state);
    void blinkDelay(int d);
    void blinkOff();
};

#endif 