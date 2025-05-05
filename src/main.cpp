/**
 ******************************************************************************
 * @file    VL53L4CX_Sat_HelloWorld.ino
 * @author  SRA
 * @version V1.0.0
 * @date    16 March 2022
 * @brief   Arduino test application for the STMicrolectronics VL53L4CX
 *          proximity sensor satellite based on FlightSense.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2022 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/
// Adapted by Calico Randall for OMSI's How Fast
// Chaining multiple ToF VL53L4CX sensors together
// April 8, 2025

#include "sensors.h"

#define LEDPIN 13

void setup() {
  // LED on board
  pinMode(LEDPIN, OUTPUT);

  // Initialize serial for output.
  while(!Serial) {
    Serial.begin(115200);
  }
  Serial.println("Beginning setup...");

  // 74HC595 Shift Register setup in sensors.h header file
  //setupShiftRegister();

  // Sensor setup in sensors.h header file
  setupSensors();
}

void loop() {
  VL53L4CX_MultiRangingData_t MultiRangingData;
  VL53L4CX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
  uint8_t num_obj_found = 0;
  int status;

  for (int i = 0; i < TOTAL_TOFS; i++) {
    status = tofs[i].VL53L4CX_WaitMeasurementDataReady();
    status = tofs[i].VL53L4CX_GetMultiRangingData(pMultiRangingData);
    num_obj_found = pMultiRangingData->NumberOfObjectsFound;
    for(int j = 0; j < num_obj_found; j++) {
      // if either sensor detects an object less than 200mm,
      // light up the red light on the board.
      if(pMultiRangingData->RangeData[j].RangeMinMilliMeter < 200) {
        digitalWrite(LEDPIN, HIGH);
        Serial.print("TOF ");
        Serial.print(i + 1);
        Serial.println(" detected object less than 200mm away.");
      } else {
        digitalWrite(LEDPIN, LOW);
      }
    }
    status = tofs[i].VL53L4CX_ClearInterruptAndStartMeasurement();
  }
  delay(100);
}