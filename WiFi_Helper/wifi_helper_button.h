
#ifndef __WIFI_BUTTON_HELPER_H__
#define __WIFI_BUTTON_HELPER_H__
#include <Arduino.h>
#include "wifi_helper_debug.h"


class WiFiButtonHelper {
  private:
	const int _shortTime = 1000;
	int _longPressTime = 6000;
	int _buttonPin;
	int _lastState;
	int _currentState;
	unsigned long _pressedTime  = 0;
	unsigned long _releasedTime = 0;
	bool _isPressing = false;
	bool _isLongDetected = false;

  public:

    WiFiButtonHelper(int pin);
    void begin();
	bool checkLongPress(int seconds);
    
};

#endif 