#pragma once

class Slider {
  public:
    Slider(int pin);

    float read() const;

    private:
      const int _pin;

};
