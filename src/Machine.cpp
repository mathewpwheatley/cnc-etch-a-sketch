#include "Machine.h"

Machine::Machine(Button &button,
                 Slider &slider,
                 Display &display,
                 Steppers &steppers,
                 Dimensions &dimensions) : _button(button),
                                           _slider(slider),
                                           _display(display),
                                           _steppers(steppers),
                                           _offsets(_calculateOffsets(dimensions)) {
                                           };

void Machine::initialize()
{
  _button.initialize();
  _display.initialize();
  _steppers.initialize();
  _state = &_resetState;
  _state->onEntry(*this);
};

void Machine::run()
{
  _state->update(*this);
}

void Machine::transitionTo(State &newState)
{
  _state->onExit(*this);
  _state = &newState;
  _state->onEntry(*this);
}

void Machine::maybeStop() {
  if (_button.read() == PressType::LONG)
  {
    _display.print("Stop Requested", "Aborting");
    _steppers.stop();
    return transitionTo(_resetState);
  }
}

Offsets Machine::_calculateOffsets(Dimensions &dimensions)
{
  float sideLengthInch = min(dimensions.heightInch, dimensions.widthInch);
  float scale = sideLengthInch * dimensions.stepsPerInch;

  float offsetX = 0.0f;
  float offsetY = 0.0f;
  if (dimensions.widthInch > dimensions.heightInch)
  {
    offsetX = ((dimensions.widthInch - sideLengthInch) / 2.0f) * dimensions.stepsPerInch;
  }
  else if (dimensions.heightInch > dimensions.widthInch)
  {
    offsetY = ((dimensions.heightInch - sideLengthInch) / 2.0f) * dimensions.stepsPerInch;
  }

  return Offsets{
      .scale = scale,
      .offsetX = offsetX,
      .offsetY = offsetY,
  };
}
