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

void setup()
{
  // LED
  pinMode(LEDPIN, OUTPUT);

  setupSensors();
}

void loop()
{
  VL53L4CX_MultiRangingData_t MultiRangingData;
  VL53L4CX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
  uint8_t NewDataReady = 0;
  int num_obj_found = 0;
  char report[64];
  int status;

  // for(int i = 0; i < TOTAL_TOFS; i++) {
  //   do {
  //     status = tofs[i].VL53L4CX_GetMeasurementDataReady(&NewDataReady);
  //   } while (!NewDataReady);

  //   if ((!status) && (NewDataReady != 0)) {
  //     status = tofs[i].VL53L4CX_GetMultiRangingData(pMultiRangingData);
  //       num_obj_found = pMultiRangingData->NumberOfObjectsFound;
  //       snprintf(report, sizeof(report), "ToF %d: Count=%d, #Objs=%1d ", i+1, pMultiRangingData->StreamCount, num_obj_found);
  //       Serial.print(report);
  //       for (int j = 0; j < num_obj_found; j++) {
  //         if (j != 0) {
  //           Serial.print("\r\n                               ");
  //         }
  //         //Serial.print("status=");
  //         //Serial.print(pMultiRangingData->RangeData[j].RangeStatus);
  //         Serial.print(", D=");
  //         Serial.print(pMultiRangingData->RangeData[j].RangeMilliMeter);
  //         Serial.print("mm");
  //         //Serial.print(", Signal=");
  //         //Serial.print((float)pMultiRangingData->RangeData[j].SignalRateRtnMegaCps / 65536.0);
  //         //Serial.print(" Mcps, Ambient=");
  //         //Serial.print((float)pMultiRangingData->RangeData[j].AmbientRateRtnMegaCps / 65536.0);
  //         //Serial.print(" Mcps");
  //         if(pMultiRangingData->RangeData[j].RangeMilliMeter < 200){
  //           digitalWrite(LEDPIN, HIGH);
  //         } else {
  //           digitalWrite(LEDPIN, LOW);
  //         }
  //       }
  //       Serial.println("");
  //       if (status == 0) {
  //         status = tofs[i].VL53L4CX_ClearInterruptAndStartMeasurement();
  //       }
  //     }
  // }

  // VL53L4CX_MultiRangingData_t MultiRangingData1, MultiRangingData2;
  // VL53L4CX_MultiRangingData_t *pMultiRangingData1 = &MultiRangingData1;
  // VL53L4CX_MultiRangingData_t *pMultiRangingData2 = &MultiRangingData2;
  // uint8_t NewDataReady = 0;
  // int no_of_obj_found_1, no_of_obj_found_2 = 0;
  // char report1[64], report2[64];
  // int status1, status2;

  // do {
  //   status1 = tof1.VL53L4CX_GetMeasurementDataReady(&NewDataReady);
  // } while (!NewDataReady);

  // if ((!status1) && (NewDataReady != 0)) {
  //   status1 = tof1.VL53L4CX_GetMultiRangingData(pMultiRangingData1);
  //   no_of_obj_found_1 = pMultiRangingData1->NumberOfObjectsFound;
  //   snprintf(report1, sizeof(report1), "ToF 1: Count=%d, #Objs=%1d ", pMultiRangingData1->StreamCount, no_of_obj_found_1);
  //   Serial.print(report1);
  //   for (int j = 0; j < no_of_obj_found_1; j++) {
  //     if (j != 0) {
  //       Serial.print("\r\n                               ");
  //     }
  //     //Serial.print("status=");
  //     //Serial.print(pMultiRangingData->RangeData[j].RangeStatus);
  //     Serial.print(", D=");
  //     Serial.print(pMultiRangingData1->RangeData[j].RangeMilliMeter);
  //     Serial.print("mm");
  //     //Serial.print(", Signal=");
  //     //Serial.print((float)pMultiRangingData->RangeData[j].SignalRateRtnMegaCps / 65536.0);
  //     //Serial.print(" Mcps, Ambient=");
  //     //Serial.print((float)pMultiRangingData->RangeData[j].AmbientRateRtnMegaCps / 65536.0);
  //     //Serial.print(" Mcps");
  //     if(pMultiRangingData1->RangeData[j].RangeMilliMeter < 200){
  //       digitalWrite(LEDPIN, HIGH);
  //     } else {
  //       digitalWrite(LEDPIN, LOW);
  //     }
  //   }
  //   Serial.println("");
  //   if (status1 == 0) {
  //     status1 = tof1.VL53L4CX_ClearInterruptAndStartMeasurement();
  //   }
  // }

  // // Check ToF 2
  // do {
  //   status2 = tof2.VL53L4CX_GetMeasurementDataReady(&NewDataReady);
  // } while (!NewDataReady);

  // if ((!status2) && (NewDataReady != 0)) {
  //   status2 = tof2.VL53L4CX_GetMultiRangingData(pMultiRangingData2);
  //   no_of_obj_found_2 = pMultiRangingData2->NumberOfObjectsFound;
  //   snprintf(report2, sizeof(report2), "ToF 2: Count=%d, #Objs=%1d ", pMultiRangingData2->StreamCount, no_of_obj_found_2);
  //   Serial.print(report2);
  //   for (int j = 0; j < no_of_obj_found_2; j++) {
  //     if (j != 0) {
  //       Serial.print("\r\n                               ");
  //     }
  //     //Serial.print("status=");
  //     //Serial.print(pMultiRangingData->RangeData[j].RangeStatus);
  //     Serial.print(", D=");
  //     Serial.print(pMultiRangingData2->RangeData[j].RangeMilliMeter);
  //     Serial.print("mm");
  //     //Serial.print(", Signal=");
  //     //Serial.print((float)pMultiRangingData->RangeData[j].SignalRateRtnMegaCps / 65536.0);
  //     //Serial.print(" Mcps, Ambient=");
  //     //Serial.print((float)pMultiRangingData->RangeData[j].AmbientRateRtnMegaCps / 65536.0);
  //     //Serial.print(" Mcps");
  //     if(pMultiRangingData2->RangeData[j].RangeMilliMeter < 200){
  //       delay(250);
  //     }
  //   }
  //   Serial.println("");
  //   if (status2 == 0) {
  //     status2 = tof2.VL53L4CX_ClearInterruptAndStartMeasurement();
  //   }
  // }
  delay(100);
}