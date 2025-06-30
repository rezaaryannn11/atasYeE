#include "DFRobot_URM09.h"

// Alamat I2C sensor URM09
#define URM09_ADDR 0x41

// Deklarasi objek sensor
DFRobot_URM09 URM09_1;

void taskURM09(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      int16_t distance = URM09_1.getDistance();
      distance_URM09_1 = distance;  // <-- Tambahkan ini!
      xSemaphoreGive(i2cMutex);

      Serial.printf("[URM09] Dist: %d cm\n", distance);
    } else {
      Serial.println("[URM09] I2C busy");
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}



/* ========= Inisialisasi URM09 ========= */
void setupUltraURM09() {
  if (!URM09_1.begin(URM09_ADDR)) {
    Serial.println("[URM09] Tidak terdeteksi!");
  } else {
    URM09_1.setModeRange(MEASURE_MODE_AUTOMATIC, MEASURE_RANG_500);
    Serial.println("[URM09] Siap digunakan");
  }
}




