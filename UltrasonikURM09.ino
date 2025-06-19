// Deklarasi sensor URM09 (2 sensor)
  DFRobot_URM09 URM09_1;
  DFRobot_URM09 URM09_2;

void setupUltraURM09() {
  while (!URM09_1.begin(0x41)) {
    Serial.println("URM09_1 I2C device error");
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  URM09_1.setModeRange(MEASURE_MODE_AUTOMATIC, 500);

  while (!URM09_2.begin(0x42)) {
    Serial.println("URM09_2 I2C device error");
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  URM09_2.setModeRange(MEASURE_MODE_AUTOMATIC, 500);

  Serial.println("URM09 initialized");
}

void TaskUltraURM09(void *pvParameters) {
  while (true) {
    int jarak1 = URM09_1.getDistance();
    int jarak2 = URM09_2.getDistance();

    bool ultra1_detected = (jarak1 > 0 && jarak1 < ULTRA_DETEKSI_CM);
    bool ultra2_detected = (jarak2 > 0 && jarak2 < ULTRA_DETEKSI_CM);

    // Cetak hasil ke Serial
    Serial.print("URM09_1: ");
    Serial.print(jarak1);
    Serial.print(" cm | Deteksi: ");
    Serial.println(ultra1_detected ? "YA" : "TIDAK");

    Serial.print("URM09_2: ");
    Serial.print(jarak2);
    Serial.print(" cm | Deteksi: ");
    Serial.println(ultra2_detected ? "YA" : "TIDAK");

    Serial.println("-----------------------------");

    // Delay RTOS 200 ms
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
