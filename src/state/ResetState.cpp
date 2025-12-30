#include "state/ResetState.h"
#include "Machine.h"

void ResetState::onEntry(Machine &machine)
{
  machine._steppers.setEnabled(false);
  machine._display.clear();
}

void ResetState::update(Machine &machine)
{
  machine.transitionTo(machine._selectingState);
}
