#include <Arduino.h>
#include "hardware/Button.h"

Button::Button(int pin) : _pin(pin) {};

void Button::initialize() const {
  pinMode(_pin, INPUT_PULLUP);
}

PressType Button::read() const
{
  static unsigned long pressTime = 0;
  static bool lastState = HIGH;
  static bool longPressTriggered = false;

  bool currentState = digitalRead(_pin);
  PressType result = PressType::NONE;

  // 1. Button just pressed (Falling Edge)
  if (lastState == HIGH && currentState == LOW)
  {
    pressTime = millis();
    longPressTriggered = false;
  }

  // 2. Button is CURRENTLY being held down
  if (currentState == LOW && !longPressTriggered)
  {
    if (millis() - pressTime > _longMilliSecond)
    {
      result = PressType::LONG;
      longPressTriggered = true;
    }
  }

  // 3. Button just released (Rising Edge)
  if (lastState == LOW && currentState == HIGH)
  {
    unsigned long duration = millis() - pressTime;

    if (!longPressTriggered && duration > _shortMilliSecond)
    {
      result = PressType::SHORT;
    }

    longPressTriggered = false;
  }

  lastState = currentState;
  return result;
}
