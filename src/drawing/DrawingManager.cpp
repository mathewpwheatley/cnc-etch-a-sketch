#include "drawing/DrawingManager.h"

bool DrawingManager::select(float selector)
{
  if (abs(selector - _previousSelector) < _hysteresis)
  {
    return false;
  }

  int newIndex = (int)(selector * DRAWINGS_COUNT);
  if (newIndex != _index)
  {
    _index = newIndex;
    _previousSelector = selector;
    return true;
  }

  return false;
}

const Drawing& DrawingManager::get() const
{
  return ALL_DRAWINGS[_index];
}
