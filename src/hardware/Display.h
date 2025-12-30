#pragma once
#include <LiquidCrystal_I2C.h>

class Display
{
public:
  Display(int address, int columns, int rows);

  void initialize();
  void clear();
  void printLine1(const char *l1);
  void printLine2(const char *l2);
  void print(const char *l1, const char *l2);
  void drawProgressBar(int percent);

  static const char DEGREE_CHAR = (char)6;

private:
  void printCentered(int row, const char *text);

  LiquidCrystal_I2C _lcd;
  const int _columns;
  const int _rows;
};
