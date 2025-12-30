#include "state/HomingState.h"
#include "Machine.h"

void HomingState::onEntry(Machine &machine)
{
  machine._display.print("Home Bottom Left", "Press to Start");
}

void HomingState::update(Machine &machine)
{
  PressType input = machine._button.read();
  if (input != PressType::NONE)
  {
    machine.transitionTo(machine._drawingState);
  }
}
