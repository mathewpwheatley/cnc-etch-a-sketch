#pragma once

enum PressType { NONE, SHORT, LONG };

class Button {
  public:
    Button(int pin);

    void initialize() const;

    PressType read() const;

  private:
    const int _pin;
    const unsigned long _shortMilliSecond = 50;
    const unsigned long _longMilliSecond = 1000;
};
