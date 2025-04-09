// Header file to set up and initialize
// all of the ToF sensors.
// Calico Randall April 8, 2025

#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cx_class.h>

#define DEV_I2C Wire

#define LEDPIN 13

#define XSHUT_PIN_1 A1
#define XSHUT_PIN_2 A2

// Addresses tested = 0x04 - 0x13
#define I2C_ADDR_1 0x04
#define I2C_ADDR_2 0x05

// Time of Flight VL53L4CX sensor declarations.
VL53L4CX tof1(&DEV_I2C, XSHUT_PIN_1);
VL53L4CX tof2(&DEV_I2C, XSHUT_PIN_2);

void setupSensors() {
    // Initialize serial for output.
    Serial.begin(115200);
    Serial.println("Beginning setup...");

    // Initialize I2C bus.
    DEV_I2C.begin();
    Serial.println("I2C bus initialized.");

    // Configure VL53L4CX satellite component.
    // Sets the shut pin as OUTPUT, then writes it to LOW
    tof1.begin();
    tof2.begin();

    // Set SHUT PIN to LOW.
    // Set to LOW, then to HIGH, then set the I2C address.
    // Repeat for each sensor.
    tof1.VL53L4CX_Off();
    tof1.InitSensor(I2C_ADDR_1);
    Serial.println("ToF1 initialized.");

    tof2.VL53L4CX_Off();
    tof2.InitSensor(I2C_ADDR_2);
    Serial.println("ToF1 initialized.");

    // Start Measurements
    tof1.VL53L4CX_StartMeasurement();
    tof2.VL53L4CX_StartMeasurement();
    Serial.println("Setup complete.");
    delay(3000);
}