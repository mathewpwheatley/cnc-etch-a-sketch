#include "state/DrawingState.h"
#include "Machine.h"

void DrawingState::onEntry(Machine &machine)
{
  char message[20];
  const char *name = machine._DrawingManager.get().name;
  snprintf(message, sizeof(message), "Draw: %s", name);
  machine._display.print(message, "");

  _segment = 0;
  machine._steppers.resume();
  machine._steppers.setHome();
}

void DrawingState::update(Machine &machine)
{
  machine.maybeStop();
  if (machine._steppers.isRunning()) {
    machine._steppers.run();
    return;
  }

  const int count = machine._DrawingManager.get().count;
  if (_segment >= count)
  {
    return machine.transitionTo(machine._finishState);
  }

  _setTarget(machine);
  int progress = ((_segment + 1) * 100) / count;
  machine._display.drawProgressBar(progress);
  return;
}

void DrawingState::_setTarget(Machine &machine) {
  const Drawing &drawing = machine._DrawingManager.get();
  float normX = pgm_read_float(&(drawing.path[_segment][0]));
  float normY = pgm_read_float(&(drawing.path[_segment][1]));

  const Offsets &offsets = machine._offsets;
  long targetX = (long)((normX * offsets.scale) + offsets.offsetX);
  long targetY = (long)((normY * offsets.scale) + offsets.offsetY);

  machine._steppers.moveTo(targetX, targetY);
  _segment++;
}
