// Header file to set up and initialize
// all of the ToF sensors.
// Calico Randall April 8, 2025

#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cx_class.h>

#define DEV_I2C Wire

#define TOTAL_TOFS 2

// Define each XSHUT pin for each ToF.
#define XSHUT_PIN_1 A1
#define XSHUT_PIN_2 A2

// Time of Flight VL53L4CX sensor declarations.
VL53L4CX tofs[TOTAL_TOFS] = { VL53L4CX(&DEV_I2C, XSHUT_PIN_1), VL53L4CX(&DEV_I2C, XSHUT_PIN_2) };

// Addresses need to be even numbers or odd numbers (not consecutive).
unsigned char I2C_ADDRESSES[] = { 0x02, 0x04 };

void setupSensors() {
    // Initialize I2C bus.
    DEV_I2C.begin();
    Serial.println("I2C bus initialized.");

    // Configure VL53L4CX satellite component.
    // Sets the shut pin as OUTPUT, then writes it to LOW.
    for(int i = 0; i < TOTAL_TOFS; i++) {
        tofs[i].begin();
        delay(100);
    }

    // Set the I2C address for each ToF.
    for(int i = 0; i < TOTAL_TOFS; i++) {
        tofs[i].VL53L4CX_Off();
        tofs[i].InitSensor(I2C_ADDRESSES[i]);
        Serial.print("ToF ");
        Serial.print(i+1);
        Serial.println(" initialized.");
        delay(100);
    }

    // Begin the measurements for each ToF.
    for(int i = 0; i < TOTAL_TOFS; i++) {
        tofs[i].VL53L4CX_StartMeasurement();
        Serial.print("Measurements started for ToF ");
        Serial.println(i+1);
        delay(100);
    }

    Serial.println("Setup complete.");
}