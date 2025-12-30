#pragma once

#include "state/State.h"

class TuningState : public State
{
public:
  void onEntry(Machine &machine) override;
  void update(Machine &machine) override;

private:
  void printBacklash(Machine &machine) const;
  int previousBacklash = 0;
};
