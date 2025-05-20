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
// Chaining multiple ToF VL53L4CX sensors together and
// having it affect sections of an LED strip based on if
// each of the ToFs has detected an object within a specific range.
// April 8, 2025

#include "tofSensors.h"
#include "ledStrip.h"

// LED pin on the Itsy Bitsy board.
#define LEDPIN 13

// Keeping count of the tubes that have successfully been completed.
// Range should be from 0 to TOTAL_TOFS.
uint8_t tubesCompleted = 0;

// Declaring the gameplay function.
uint8_t gameplay(uint8_t completed);

void setup() {
  // LED on board
  pinMode(LEDPIN, OUTPUT);

  // Initialize serial for output.
  while(!Serial) {
    Serial.begin(115200);
  }
  Serial.println("Beginning setup...");

  // Sensor setup in sensors.h header file.
  setupSensors();

  // LED Strip setup in ledStrip.h header file.
  setupLEDStrip();
}

void loop() {
  // While the total number of tubes completed is less than
  // the total ToFs, continue the game play.
  while(tubesCompleted < TOTAL_TOFS) {
    Serial.print("Tubes completed = ");
    Serial.println(tubesCompleted);

    lightSections(tubesCompleted);

    // Update the tubes completed as the game is played.
    tubesCompleted = gameplay(tubesCompleted);

    delay(100);
  }

  lightSections(tubesCompleted);
  Serial.println("All tubes completed!");
  Serial.print("tubesCompleted = ");
  Serial.println(tubesCompleted);
  delay(500);
  gameCompleted();
}

// Gameplay for tracking each tube that has been completed when an
// object is detected within a specific range of the ToF.
uint8_t gameplay(uint8_t completed) {
  VL53L4CX_MultiRangingData_t MultiRangingData;
  VL53L4CX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;

  int status = tofs[completed].VL53L4CX_WaitMeasurementDataReady();
  status = tofs[completed].VL53L4CX_GetMultiRangingData(pMultiRangingData);
  uint8_t num_obj_found = pMultiRangingData->NumberOfObjectsFound;

  for(int j = 1; j < num_obj_found; j++) {
    // If the sensor detects something within a certain range,
    // light up the corresponding section of the tube and 
    // look at the next ToF.
    if(j > 1 && pMultiRangingData->RangeData[j].RangeMinMilliMeter <= 200) {
      digitalWrite(LEDPIN, HIGH);
      Serial.print("TOF ");
      Serial.print(completed + 1);
      Serial.println(" completed.");
      //delay(100);

      // Add one to the number of tubes completed if object detected within
      // a specific range. 
      // If we were at the last tube, return TOTAL_TOFS. 
      if(completed + 1 == TOTAL_TOFS) {
        return TOTAL_TOFS;
      } else {
        completed++;
      }
    } else {
      // Keep this for future testing. If something wrong with LEDs,
      // the LED pin on the board will indicate that.
      digitalWrite(LEDPIN, LOW);
    }
  }
  status = tofs[completed].VL53L4CX_ClearInterruptAndStartMeasurement();
  return completed;
}