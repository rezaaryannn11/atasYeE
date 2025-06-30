// Deklarasi sensor kamera
HUSKYLENS huskylens;

void setupHuskylens() {
  if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
    if (huskylens.begin(Wire)) {
      Serial.println("[HUSKYLENS] Tersambung");
    } else {
      Serial.println("[HUSKYLENS] Gagal koneksi");
    }
    xSemaphoreGive(i2cMutex);
  }
  Serial.println("[HUSKYLENS] Siap digunakan");
}

void taskHuskylens(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
      if (!huskylens.request()) {
        Serial.println("[HUSKYLENS] Gagal meminta data!");
        huskyID = -1;
      } else if (!huskylens.isLearned()) {
        Serial.println("[HUSKYLENS] Belum ada objek yang dipelajari");
        huskyID = -1;
      } else if (!huskylens.available()) {
        Serial.println("[HUSKYLENS] Tidak ada objek terdeteksi");
        huskyID = -1;
      } else {
        while (huskylens.available()) {
          HUSKYLENSResult result = huskylens.read();

          if (result.command == COMMAND_RETURN_BLOCK) {
            huskyX = result.xCenter;
            huskyY = result.yCenter;
            huskyWidth = result.width;
            huskyHeight = result.height;
            huskyID = result.ID;

            Serial.printf("[HUSKYLENS] ID=%d x=%d y=%d w=%d h=%d\n",
                          huskyID, huskyX, huskyY, huskyWidth, huskyHeight);

            if (huskyID == 1) {
              Serial.println("[HUSKYLENS] Korban terdeteksi!");
            }
          } else {
            Serial.println("[HUSKYLENS] Objek tidak dikenali!");
          }
        }
      }
      xSemaphoreGive(i2cMutex);
    } else {
      Serial.println("[HUSKYLENS] I2C busy");
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
