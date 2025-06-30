// // Deklarasi sensor ToF VL53L0X (4 sensor)
// Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// // Inisialisasi sensor ToF
// void setupToF() {
//   if (!lox1.begin(0x60)) Serial.println(F("VL53L0X 0x60 gagal"));
//   if (!lox2.begin(0x61)) Serial.println(F("VL53L0X 0x61 gagal"));
//   if (!lox3.begin(0x62)) Serial.println(F("VL53L0X 0x62 gagal"));
//   if (!lox4.begin(0x63)) Serial.println(F("VL53L0X 0x63 gagal"));

//   Serial.println(F("Semua VL53L0X di-inisialisasi"));
// }

// // Task pembacaan sensor ToF
// void taskToF(void *pvParameters) {
//   VL53L0X_RangingMeasurementData_t m;

//   for (;;) {
//     if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
//       // Sensor 1
//       lox1.rangingTest(&m, false);
//       distance_tof1 = (m.RangeStatus == 0) ? m.RangeMilliMeter : -1;

//       // Sensor 2
//       lox2.rangingTest(&m, false);
//       distance_tof2 = (m.RangeStatus == 0) ? m.RangeMilliMeter : -1;

//       // Sensor 3
//       lox3.rangingTest(&m, false);
//       distance_tof3 = (m.RangeStatus == 0) ? m.RangeMilliMeter : -1;

//       // Sensor 4
//       lox4.rangingTest(&m, false);
//       distance_tof4 = (m.RangeStatus == 0) ? m.RangeMilliMeter : -1;

//       xSemaphoreGive(i2cMutex);

//       Serial.printf("[ToF] 60: %4d | 61: %4d | 62: %4d | 63: %4d\n",
//                     distance_tof1, distance_tof2, distance_tof3, distance_tof4);
//     } else {
//       Serial.println("[ToF] I2C busy");
//     }
//     vTaskDelay(pdMS_TO_TICKS(300)); // frekuensi baca ~3Hz
//   }
// }

