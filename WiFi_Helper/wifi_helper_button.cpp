#include <Arduino.h>
#include "wifi_helper_button.h"

WiFiButtonHelper::WiFiButtonHelper(int pin)
{
	_buttonPin = pin;
}

void WiFiButtonHelper::begin()
{
	pinMode(_buttonPin, INPUT_PULLUP);
}

bool WiFiButtonHelper::checkLongPress(int seconds)
{
	_longPressTime = seconds * 1000;
	_currentState = digitalRead(_buttonPin);
	_isLongDetected = false;
	if (_lastState == HIGH && _currentState == LOW)
	{ // button is pressed
		_pressedTime = millis();
		_isPressing = true;
		_isLongDetected = false;
	}
	else if (_lastState == LOW && _currentState == HIGH)
	{ // button is released
		_isPressing = false;
		_releasedTime = millis();

		long pressDuration = _releasedTime - _pressedTime;

		if (pressDuration < _shortTime)
		{
			DEBUG_PRINTLN("A short press is detected");
			
		}
	}
	if (_isPressing == true && _isLongDetected == false)
	{
		long pressDuration = millis() - _pressedTime;
		if (pressDuration > _longPressTime)
		{
			DEBUG_PRINTLN("A long press is detected");
			_isLongDetected = true;
		}
	}
	_lastState = _currentState;
	return (_isLongDetected == true) ?  true :  false;
}
