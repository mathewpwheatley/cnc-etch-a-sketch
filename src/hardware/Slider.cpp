#include <Arduino.h>
#include "hardware/Slider.h"

namespace
{
  constexpr int MAX_POT_READ_VALUE = 1024;
}

Slider::Slider(int pin) : _pin(pin) {};

float Slider::read() const
{
  // Return is normalized
  return (float)analogRead(_pin) / MAX_POT_READ_VALUE;
};
