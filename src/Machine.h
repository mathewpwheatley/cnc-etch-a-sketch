#pragma once

#include <Arduino.h>
#include "hardware/Button.h"
#include "hardware/Slider.h"
#include "hardware/Display.h"
#include "hardware/Steppers.h"
#include "drawing/DrawingManager.h"
#include "state/State.h"
#include "state/ResetState.h"
#include "state/SelectingState.h"
#include "state/HomingState.h"
#include "state/DrawingState.h"
#include "state/FinishState.h"
#include "state/TuningState.h"

struct Dimensions {
  float widthInch;
  float heightInch;
  float stepsPerInch;
};

struct Offsets {
  const float scale;
  const float offsetX;
  const float offsetY;
};

class Machine
{
  friend class ResetState;
  friend class SelectingState;
  friend class HomingState;
  friend class DrawingState;
  friend class FinishState;
  friend class TuningState;

public:
  Machine(
      Button& button,
      Slider& slider,
      Display& display,
      Steppers& steppers,
      Dimensions& dimensions);

  void initialize();
  void run();
  void transitionTo(State& state);

  void maybeStop();

private:
  Offsets _calculateOffsets(Dimensions& dimensions);

  Button& _button;
  Slider& _slider;
  Display& _display;
  Steppers& _steppers;

  DrawingManager _DrawingManager;
  const Offsets _offsets;

  State *_state;
  // Pre-allocate states to avoid dynamic memory (New/Delete) on Arduino
  ResetState _resetState;
  SelectingState _selectingState;
  HomingState _homingState;
  DrawingState _drawingState;
  FinishState _finishState;
  TuningState _tuningState;
};
