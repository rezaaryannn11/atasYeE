// Inisialisasi sensor BNO055
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29); // Alamat default 0x28, bisa juga 0x29 tergantung ADDR pin

void setupIMUBNO055() {
  Serial.begin(115200);
  vTaskDelay(pdMS_TO_TICKS(200));
  Serial.println("Adafruit BNO055 - Euler Angles (Yaw, Pitch, Roll)");

  // Mulai komunikasi dengan sensor
  if (!bno.begin()) {
    Serial.print("Tidak dapat menemukan BNO055. Periksa kabel dan alamat I2C!");
    while (1);
  }

  // Set mode operasi sensor
  bno.setExtCrystalUse(true); // Gunakan kristal eksternal untuk akurasi lebih baik

  vTaskDelay(pdMS_TO_TICKS(200));
}


void taskIMUBNO055(void *pvParameters) {
  while (true) {
    // Baca data orientasi
    sensors_event_t orientationData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

    // Baca sudut Euler (Yaw, Pitch, Roll)
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    
    Yaw = euler.x();   // Heading
    Pitch = euler.y(); // Pitch
    Roll = euler.z();  // Roll

    // Debug ke Serial Monitor
    Serial.print("Yaw: ");
    Serial.print(Yaw);
    Serial.print("°, Pitch: ");
    Serial.print(Pitch);
    Serial.print("°, Roll: ");
    Serial.println(Roll);

    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

