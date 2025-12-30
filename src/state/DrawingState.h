#pragma once

#include "state/State.h"

class DrawingState : public State
{
public:
  void onEntry(Machine &machine) override;
  void update(Machine &machine) override;

private:
  int _segment = 0;

  void _setTarget(Machine &machine);
};
