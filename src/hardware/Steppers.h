#pragma once

#include <AccelStepper.h>

enum class Axis : int
{
  X = 0,
  Y = 1,
  COUNT = 2
};

struct AxisState
{
  long position = 0;
  bool lastMovePositive = true;
};

class Steppers
{
public:
  Steppers(
      AccelStepper &stepperX,
      AccelStepper &stepperY,
      float maxSpeed,
      float acceleration,
      int stepsPerRotation,
      int backlashEepromAddress);

  void initialize();
  void setEnabled(bool enable = true);
  void moveTo(long absoluteX, long absoluteY);
  void resume();
  bool isRunning();
  void run();
  void stop();

  int getBacklash();
  void setBacklash(long backlashSteps);
  int stepsToDegree(long steps);
  long degreesToSteps(int degrees);
  void setHome();

private:
  long _applyBacklash(long absoluteTarget, Axis axis);

  AccelStepper &_stepperX;
  AccelStepper &_stepperY;
  const int _stepsPerRotation;
  const int _backlashEepromAddress;

  long _backlash = 0;
  AxisState _axes[2];
  volatile bool _isStopped = false; // 'volatile' for interrupt safety
};
