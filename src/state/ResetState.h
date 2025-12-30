#pragma once

#include "state/State.h"

class ResetState : public State
{
public:
  void onEntry(Machine &machine) override;
  void update(Machine &machine) override;
};
