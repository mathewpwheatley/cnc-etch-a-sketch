#pragma once

class Machine; // Forward declaration

class State
{
public:
  virtual ~State() {}

  virtual void onEntry(Machine &machine) {}
  virtual void update(Machine &machine) = 0;
  virtual void onExit(Machine &machine) {}
};
