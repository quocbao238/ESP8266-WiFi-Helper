#include <Arduino.h>
#include "wifi_helper_led.h"

/*
 * Resets all timers and state
 */
void WiFiLedHelper::reset() {
  m_blinkTime   = 0UL;
  m_onForTime   = -1;
  m_offForTime  = -1;
  m_blinkState  = BLINK_OFF;
  m_resolution  = 100;
}


/*
 * Constructor. Only needs to know what pin to blink.
 */
WiFiLedHelper::WiFiLedHelper(int pin) {
  m_pin = pin;
  reset();
}

void WiFiLedHelper::begin(){
  pinMode(m_pin,OUTPUT);
}


/*
 * Sets the blink time ON
 */
void WiFiLedHelper::setOnTime(int ms) {
  if (ms>0) { // no=op if ms is <= 0
    m_onForTime = ms;
    if (m_offForTime>0) {
      m_resolution = min(m_onForTime,m_offForTime)/10;
    }
  }
}

/*
 * Sets the blink time OFF
 */
void WiFiLedHelper::setOffTime(int ms) {
  if (ms>0) { // no=op if ms is <= 0
    m_offForTime = ms;
    if (m_onForTime>0) {
      m_resolution = min(m_onForTime,m_offForTime);
    }
  }
}

/*
 * Sets the blink state ON or OFF
 */
void WiFiLedHelper::setBlinkState(blink_t state)
{
  digitalWrite(m_pin, (state==BLINK_ON) ? HIGH : LOW);
  m_blinkState = state;
  m_blinkTime  = millis();
}

/*
 * Executes the blink. It allows to specify new on and off times. Use negative
 * values if you don't want to change what is already set.
 */

void WiFiLedHelper::blink(int on_for, int off_for) {

  unsigned long ct = millis();
  if (m_blinkTime==0UL) m_blinkTime=ct;
  unsigned long diff = abs(ct - m_blinkTime);
  short set_to = -1;

  setOnTime(on_for);
  setOffTime(off_for);

  if (m_blinkState==BLINK_OFF) {
    if (m_offForTime>0 && diff>m_offForTime) {
      setBlinkState(BLINK_ON);
    }
  } else {
    if (m_onForTime>0 && diff>m_onForTime) {
      setBlinkState(BLINK_OFF);
    }
  }
}

/*
 * Call often to blink.
 */
void WiFiLedHelper::blink() {
  blink(-1,-1);
}

/*
 * Equivalent to delay(d), but updates the blink.
 */
void WiFiLedHelper::blinkDelay(int d)
{
  unsigned long ct = millis();
  while (millis()-ct<d) {
    blink();
    delay(m_resolution);
  }
}

/*
 * Turns off the blink.
 */
void WiFiLedHelper::blinkOff() {
  reset();
  digitalWrite(m_pin, LOW);
}