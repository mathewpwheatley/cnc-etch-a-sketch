#include "state/SelectingState.h"
#include "Machine.h"

void SelectingState::onEntry(Machine &machine)
{
  machine._display.print("Select Drawing", machine._DrawingManager.get().name);
}

void SelectingState::update(Machine &machine)
{
  if (machine._DrawingManager.select(machine._slider.read()))
  {
    machine._display.print("Select Drawing", machine._DrawingManager.get().name);
  }

  PressType input = machine._button.read();
  if (input == PressType::SHORT)
  {
    machine.transitionTo(machine._homingState);
  }
  if (input == PressType::LONG)
  {
    machine.transitionTo(machine._tuningState);
  }
}
