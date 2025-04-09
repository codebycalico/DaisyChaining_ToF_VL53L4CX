// Header file to set up and initialize
// all of the ToF sensors.
// Calico Randall April 8, 2025

#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cx_class.h>

#define DEV_I2C Wire

#define LEDPIN 13

#define TOTAL_TOFS 2

#define XSHUT_PIN_1 A1
#define XSHUT_PIN_2 A2

// Addresses tested = 0x04 - 0x13
#define I2C_ADDR_1 0x04
#define I2C_ADDR_2 0x05

// Time of Flight VL53L4CX sensor declarations.
//VL53L4CX tof1(&DEV_I2C, XSHUT_PIN_1);
//VL53L4CX tof2(&DEV_I2C, XSHUT_PIN_2);

VL53L4CX tofs[TOTAL_TOFS];
unsigned char I2C_ADDRESSES[] = { 0x04, 0x02 };
unsigned char XSHUT_PINS[] = { A1, A2 };

void setupSensors() {
    // Initialize serial for output.
    Serial.begin(115200);
    Serial.println("Beginning setup...");

    // Initialize I2C bus.
    DEV_I2C.begin();
    Serial.println("I2C bus initialized.");

    // Configure VL53L4CX satellite component.
    // Sets the shut pin as OUTPUT, then writes it to LOW
    for(int i = 0; i < TOTAL_TOFS; i++) {
        tofs[i] = VL53L4CX(&DEV_I2C, XSHUT_PINS[i]);
        tofs[i].begin();
    }
    for(int i = 0; i < TOTAL_TOFS; i++) {
        tofs[i].VL53L4CX_Off();
        tofs[i].InitSensor(I2C_ADDRESSES[i]);
        Serial.print("ToF ");
        Serial.print(i+1);
        Serial.println(" initialized.");
    }
    for(int i = 0; i < TOTAL_TOFS; i++) {
        tofs[i].VL53L4CX_StartMeasurement();
        Serial.print("Measurements started for ToF ");
        Serial.println(i+1);
    }
    //tof1.begin();
    //tof2.begin();

    // Set SHUT PIN to LOW.
    // Set to LOW, then to HIGH, then set the I2C address.
    // Repeat for each sensor.
    // tof1.VL53L4CX_Off();
    // tof1.InitSensor(I2C_ADDR_1);
    // Serial.println("ToF1 initialized.");

    // tof2.VL53L4CX_Off();
    // tof2.InitSensor(I2C_ADDR_2);
    // Serial.println("ToF1 initialized.");

    // Start Measurements
    //tof1.VL53L4CX_StartMeasurement();
    //tof2.VL53L4CX_StartMeasurement();
    Serial.println("Setup complete.");
    //delay(3000);
}