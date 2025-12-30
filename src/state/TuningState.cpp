#include "state/TuningState.h"
#include "Machine.h"

namespace
{
  constexpr int MAX_BACKLASH_ADJUSTMENT_DEGREES = 30;
}

void TuningState::onEntry(Machine &machine)
{
  machine._display.print("Tuning Backlash", "");
  printBacklash(machine);
}

void TuningState::update(Machine &machine)
{
  int value = machine._slider.read() * MAX_BACKLASH_ADJUSTMENT_DEGREES;
  if (value != previousBacklash)
  {
    previousBacklash = value;
    printBacklash(machine);
  }
  PressType input = machine._button.read();
  if (input != PressType::NONE)
  {
    if (input == PressType::SHORT)
    {
      machine._steppers.setBacklash(value);
    }
    machine.transitionTo(machine._resetState);
  }
}

void TuningState::printBacklash(Machine &machine) const
{
  int set = machine._steppers.getBacklash();
  int current = machine._slider.read() * MAX_BACKLASH_ADJUSTMENT_DEGREES;
  char message[20];
  snprintf(message, sizeof(message), "Set:%d%c New:%d%c", set, Display::DEGREE_CHAR, current, Display::DEGREE_CHAR);
  machine._display.printLine2(message);
}
