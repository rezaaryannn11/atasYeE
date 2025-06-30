// Callback pengiriman
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Status pengiriman: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SUKSES" : "GAGAL");
}

void setupESPNOW() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);

  if (esp_now_init() != ESP_OK) {
    Serial.println("[ESP-NOW] Inisialisasi gagal!");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_is_peer_exist(receiverAddress)) {
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("[ESP-NOW] Gagal menambahkan peer");
      return;
    }
  }

  Serial.println("[ESP-NOW] Siap digunakan");
}


// Fungsi untuk kirim data ke penerima
void loopkirimDataESPNow() {

  // 2. Kirim data
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *)&myMessage, sizeof(myMessage));

  // 3. Tampilkan status pengiriman dan isi data
  if (result == ESP_OK) {
    Serial.print(" | Perintah= {");
    for (int i = 0; i < 6; i++) {
      Serial.print(myMessage.dataPerintah[i] ? "1" : "0");
      if (i < 5) Serial.print(", ");
    }
    Serial.println("}");
  } else {
    Serial.println("Gagal kirim data");
  }
}


void komunikasiESPNOW(char gerak) {
  bool arr[6] = {0, 0, 0, 0, 0, 0}; // Default

  // Gunakan array tetap untuk setiap perintah
  switch (gerak) {
    case 'Z': { const bool temp[] = {0,0,0,0,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'A': { const bool temp[] = {0,0,0,0,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'B': { const bool temp[] = {0,0,0,0,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'C': { const bool temp[] = {0,0,0,1,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'D': { const bool temp[] = {0,0,1,1,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'E': { const bool temp[] = {0,1,1,1,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'F': { const bool temp[] = {1,1,1,1,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'G': { const bool temp[] = {1,1,1,1,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'H': { const bool temp[] = {1,1,1,0,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'I': { const bool temp[] = {1,1,0,0,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'J': { const bool temp[] = {1,0,0,0,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'K': { const bool temp[] = {1,1,1,1,1,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'L': { const bool temp[] = {1,1,1,1,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'M': { const bool temp[] = {1,1,1,0,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'N': { const bool temp[] = {1,1,0,0,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'O': { const bool temp[] = {1,0,0,0,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'P': { const bool temp[] = {1,0,0,1,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'Q': { const bool temp[] = {1,0,1,1,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'R': { const bool temp[] = {1,0,1,1,1,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'S': { const bool temp[] = {1,0,1,1,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'T': { const bool temp[] = {0,1,1,0,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'U': { const bool temp[] = {0,1,0,0,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'V': { const bool temp[] = {0,1,0,0,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'W': { const bool temp[] = {0,1,0,0,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'X': { const bool temp[] = {0,0,1,1,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'a': { const bool temp[] = {1,1,0,0,1,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'b': { const bool temp[] = {1,0,1,0,1,0}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'c': { const bool temp[] = {0,1,0,1,0,1}; memcpy(arr, temp, sizeof(arr)); break; }
    case 'd': { const bool temp[] = {1,1,1,0,0,0}; memcpy(arr, temp, sizeof(arr)); break; }
    default: {
      const bool temp[] = {0,0,0,0,0,0};
      memcpy(arr, temp, sizeof(arr));
      Serial.printf("[ESP-NOW] Perintah '%c' tidak dikenal, kirim default 000000\n", gerak);
      break;
    }
  }

  // Debug output sebelum kirim
  Serial.print("[ESP-NOW] Kirim gerak '");
  Serial.print(gerak);
  Serial.print("' -> data: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(arr[i]);
  }
  Serial.println();

  // Kirim data lewat ESP-NOW
  memcpy(myMessage.dataPerintah, arr, sizeof(arr));
  esp_now_send(receiverAddress, (uint8_t *) &myMessage, sizeof(myMessage));
}

