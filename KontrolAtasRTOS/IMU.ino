// Inisialisasi sensor BNO055
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29); // Alamat default 0x28, 0x29 jika ADDR ke VCC

void taskBNO055(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      imu::Vector<3> eul = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      xSemaphoreGive(i2cMutex);

      Yaw = eul.x();
      Pitch = eul.y();
      Roll = eul.z();

      Serial.printf("[IMU] Yaw: %.1f°  Pitch: %.1f°  Roll: %.1f°\n", Yaw, Pitch, Roll);
    } else {
      Serial.println("[IMU] I2C busy");
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

/* ========= Setup IMU BNO055 ========= */
void setupIMUBNO055() {
  Serial.println("[BNO055] Inisialisasi...");

  if (!bno.begin()) {
    Serial.println("[BNO055] Tidak terdeteksi!");
  } else {
    bno.setExtCrystalUse(true);
    Serial.println("[BNO055] Terdeteksi dan siap");
  }
}


