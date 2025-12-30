#include <Arduino.h>
#include "config.h"
#include "Machine.h"

Button button{BTN_PIN};
Slider slider{POT_PIN};
Display display{LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS};
AccelStepper stepperX{AccelStepper::FULL4WIRE, X_PIN1, X_PIN2, X_PIN3, X_PIN4};
AccelStepper stepperY{AccelStepper::FULL4WIRE, Y_PIN1, Y_PIN2, Y_PIN3, Y_PIN4};
Steppers steppers{stepperX, stepperY, STEPPER_MAX_SPEED, STEPPER_ACCELERATION, STEPPER_STEPS_PER_ROTATION, STEPPER_BACKLASH_EEPROM_ADDRESS};
Dimensions dimensions{MACHINE_WIDTH_IN, MACHINE_HEIGHT_IN, STEPS_PER_INCH};

Machine machine(button, slider, display, steppers, dimensions);

void setup()
{
  Serial.begin(9600);
  machine.initialize();

  display.print("CNC", "Etch-A-Sketch");
  delay(2500);
}

void loop()
{
  machine.run();
}
