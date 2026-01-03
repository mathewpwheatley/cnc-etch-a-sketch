#include <EEPROM.h>
#include "hardware/Steppers.h"

Steppers::Steppers(
    AccelStepper &stepperX,
    AccelStepper &stepperY,
    float maxSpeed,
    float acceleration,
    int stepsPerRotation,
    int backlashEepromAddress) : _stepperX(stepperX),
                                 _stepperY(stepperY),
                                 _stepsPerRotation(stepsPerRotation),
                                 _backlashEepromAddress(backlashEepromAddress)
{
  _stepperX.setMaxSpeed(maxSpeed);
  _stepperY.setMaxSpeed(maxSpeed);
  _stepperX.setAcceleration(acceleration);
  _stepperY.setAcceleration(acceleration);
};

void Steppers::initialize()
{
  int value;
  EEPROM.get(_backlashEepromAddress, value);
  _backlash = value;
}

void Steppers::setEnabled(bool enable)
{
  if (enable)
  {
    _stepperX.enableOutputs();
    _stepperY.enableOutputs();
  }
  else
  {
    _stepperX.disableOutputs();
    _stepperY.disableOutputs();
  }
}

void Steppers::moveTo(long absoluteX, long absoluteY)
{
  if (_isStopped)
    return;

  _stepperX.moveTo(_applyBacklash(absoluteX, Axis::X));
  _stepperY.moveTo(_applyBacklash(absoluteY, Axis::Y));
  _axes[static_cast<int>(Axis::X)].position = absoluteX;
  _axes[static_cast<int>(Axis::Y)].position = absoluteY;
}

long Steppers::_applyBacklash(long absoluteTarget, Axis axis)
{
  AxisState &a = _axes[static_cast<int>(axis)];
  bool movePositive = (absoluteTarget >= a.position);
  if (absoluteTarget == a.position || movePositive == a.lastMovePositive)
  {
    return absoluteTarget;
  }
  a.lastMovePositive = movePositive;
  return movePositive ? (absoluteTarget + _backlash) : (absoluteTarget - _backlash);
}

void Steppers::resume()
{
  _isStopped = false;
  setEnabled();
}

void Steppers::setHome()
{
  _stepperX.setCurrentPosition(0);
  _stepperY.setCurrentPosition(0);
}

bool Steppers::isRunning()
{
  return _stepperX.isRunning() || _stepperY.isRunning();
}

void Steppers::run()
{
  _stepperX.run();
  _stepperY.run();
}

void Steppers::stop()
{
  _isStopped = true;
  _stepperX.stop();
  _stepperY.stop();
}

int Steppers::getBacklash()
{
  return _backlash;
}

void Steppers::setBacklash(long steps)
{
  _backlash = steps;
  EEPROM.put(_backlashEepromAddress, _backlash);
}

int Steppers::stepsToDegree(long steps)
{
  return (int)((static_cast<long>(steps) * 360) / _stepsPerRotation);
}

long Steppers::degreesToSteps(int degrees)
{
  return (static_cast<long>(degrees) * _stepsPerRotation) / 360;
}
