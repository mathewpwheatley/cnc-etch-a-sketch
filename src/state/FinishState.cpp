#include "state/FinishState.h"
#include "Machine.h"

void FinishState::onEntry(Machine &machine)
{
  machine._display.print("Finished Drawing", "Going Home");
  const Offsets &offsets = machine._offsets;
  machine._steppers.moveTo(0 - offsets.offsetX, 0 - offsets.offsetY);
}

void FinishState::update(Machine &machine)
{
  machine.maybeStop();
  if (machine._steppers.isRunning())
  {
    machine._steppers.run();
    return;
  }
  return machine.transitionTo(machine._resetState);
}
