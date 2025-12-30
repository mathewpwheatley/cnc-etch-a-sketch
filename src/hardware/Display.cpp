#include <Arduino.h>
#include "hardware/Display.h"

namespace
{
  byte bar1[8] = {
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000};

  byte bar2[8] = {
      B11000,
      B11000,
      B11000,
      B11000,
      B11000,
      B11000,
      B11000,
      B11000};

  byte bar3[8] = {
      B11100,
      B11100,
      B11100,
      B11100,
      B11100,
      B11100,
      B11100,
      B11100};

  byte bar4[8] = {
      B11110,
      B11110,
      B11110,
      B11110,
      B11110,
      B11110,
      B11110,
      B11110};

  byte bar5[8] = {
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111};

  byte degree[8] = {
      B00110,
      B01001,
      B01001,
      B00110,
      B00000,
      B00000,
      B00000,
      B00000};
}

Display::Display(
    int address,
    int columns,
    int rows) : _lcd(LiquidCrystal_I2C(address, columns, rows)),
                _columns(columns),
                _rows(rows) {};

void Display::initialize()
{
  _lcd.init();
  _lcd.createChar(1, bar1);
  _lcd.createChar(2, bar2);
  _lcd.createChar(3, bar3);
  _lcd.createChar(4, bar4);
  _lcd.createChar(5, bar5);
  _lcd.createChar(6, degree);
  _lcd.backlight();
}

void Display::clear()
{
  _lcd.clear();
}
void Display::printLine1(const char *l1)
{
  printCentered(0, l1);
}

void Display::printLine2(const char *l2)
{
  printCentered(1, l2);
}

void Display::print(const char *l1, const char *l2)
{
  printLine1(l1);
  printLine2(l2);
}

void Display::drawProgressBar(int percent)
{
  int totalPixels = map(percent, 0, 100, 0, _columns * 5);

  int fullBlocks = totalPixels / 5;
  int partialPixels = totalPixels % 5;

  _lcd.setCursor(0, _rows - 1);

  for (int i = 0; i < _columns; i++)
  {
    if (i < fullBlocks)
    {
      _lcd.write(5); // Solid block
    }
    else if (i == fullBlocks && partialPixels > 0)
    {
      _lcd.write(partialPixels); // Custom char 1, 2, 3, or 4
    }
    else
    {
      _lcd.print(" "); // Empty space
    }
  }
}

void Display::printCentered(int row, const char *text)
{
  // 1. Create a buffer filled with spaces (plus null terminator)
  char buffer[_columns + 1];
  for (int i = 0; i < _columns; i++)
    buffer[i] = ' ';
  buffer[_columns] = '\0';

  // 2. Calculate offset to center the text
  int len = strlen(text);
  if (len > _columns)
    len = _columns; // Safety check
  int offset = (_columns - len) / 2;

  // 3. Copy the text into the middle of the space-filled buffer
  memcpy(buffer + offset, text, len);

  // 4. Print the entire line
  _lcd.setCursor(0, row);
  _lcd.print(buffer);
}
