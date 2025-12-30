#pragma once

#include "config.h"
#include "drawing/Drawing.h"
#include "drawing/drawing_data.h"

class DrawingManager
{
public:
  DrawingManager() = default;

  bool select(float selectionFactor);

  const Drawing& get() const;

private:
  int _index = 0;
  float _previousSelector = 0;
  const float _hysteresis = 0.05f;
};
