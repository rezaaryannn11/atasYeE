void taskKeputusan(void *pvParameters) {
  for (;;) {
    // Cek hanya dua kondisi, tidak perlu pakai for (i = 1..20) kalau hanya rintangan_[1] dan [2]
    
    if (!rintangan_[1]) {
      if (distance_URM09_1 <= 5) {
        komunikasiESPNOW('B');
        Serial.println("[KEPUTUSAN] Kirim perintah: B (Obstacle dekat)");
        rintangan_[1] = true;
      }
    }

    if (!rintangan_[2]) {
      if (distance_URM09_1 >= 30) {
        komunikasiESPNOW('C');
        Serial.println("[KEPUTUSAN] Kirim perintah: C (Obstacle jauh)");
        rintangan_[2] = true;
      }
    }

    // Tambahkan delay
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}


  //   else if (distance_URM09_1 < 10 && (Yaw >= 85 && Yaw <= 95)) {
  //     komunikasiESPNOW('S');
  //     Serial.println("[KEPUTUSAN] Kirim perintah: S (Tengah + obstacle sedang)");
  //   }
  //   else if (Yaw < 45) {
  //     komunikasiESPNOW('L');
  //     Serial.println("[KEPUTUSAN] Kirim perintah: L (Putar kiri)");
  //   }
  //   else if (Yaw > 135) {
  //     komunikasiESPNOW('R');
  //     Serial.println("[KEPUTUSAN] Kirim perintah: R (Putar kanan)");
  //   }
  //   else {
  //     komunikasiESPNOW('A');
  //     Serial.println("[KEPUTUSAN] Kirim perintah: A (Default maju)");
  //   }

  //   vTaskDelay(pdMS_TO_TICKS(500));
  // }

