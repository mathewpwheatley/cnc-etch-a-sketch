#pragma once

#include <Arduino.h>

// --- Physical Machine Constraints ---
constexpr float STEPS_PER_INCH = 140.0f;
constexpr float MACHINE_WIDTH_IN = 6.0f;
constexpr float MACHINE_HEIGHT_IN = 4.25f;
constexpr long MAX_X = static_cast<long>(MACHINE_WIDTH_IN * STEPS_PER_INCH);
constexpr long MAX_Y = static_cast<long>(MACHINE_HEIGHT_IN * STEPS_PER_INCH);

// --- LCD Constants ---
// Wiring: SDA pin is connected to A4 and SCL pin to A5
constexpr uint8_t LCD_ADDRESS = 0x27;
constexpr uint8_t LCD_COLUMNS = 16;
constexpr uint8_t LCD_ROWS = 2;

// --- Pin Definitions ---
constexpr uint8_t BTN_PIN = A0;
constexpr uint8_t POT_PIN = A1;

constexpr uint8_t X_PIN1 = 8;
constexpr uint8_t X_PIN2 = 7;
constexpr uint8_t X_PIN3 = 6;
constexpr uint8_t X_PIN4 = 5;

constexpr uint8_t Y_PIN1 = 12;
constexpr uint8_t Y_PIN2 = 11;
constexpr uint8_t Y_PIN3 = 10;
constexpr uint8_t Y_PIN4 = 9;

// --- Stepper Motor Tuning ---
constexpr int STEPPER_MAX_SPEED = 1000;
constexpr int STEPPER_ACCELERATION = STEPPER_MAX_SPEED/2;
constexpr int STEPPER_STEPS_PER_ROTATION = 200;

// --- Memory Management ---
constexpr int STEPPER_BACKLASH_EEPROM_ADDRESS = 0;
