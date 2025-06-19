// Callback pengiriman
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Status pengiriman: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SUKSES" : "GAGAL");
}

// Inisialisasi ESP-NOW
void setupESPNOW() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  vTaskDelay(pdMS_TO_TICKS(200));

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init gagal");
    return;
  }

  // Registrasi callback
  esp_now_register_send_cb(OnDataSent);

  // Tambahkan peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  // channel harus sama dengan pengirim & penerima
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan peer ESP-NOW");
    return;
  }

  Serial.println("ESP-NOW siap");
}

// Fungsi untuk kirim data ke penerima
void loopkirimDataESPNow() {
  // 1. Update data 
  myMessage.ultra_detected = ultra_detected;
  myMessage.tof_detected = tof_detected;
  myMessage.imu_heading = imu_heading;
  myMessage.huskyID = huskyID;

  // 2. Kirim data
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *)&myMessage, sizeof(myMessage));

  // 3. Tampilkan status pengiriman dan isi data
  if (result == ESP_OK) {
    Serial.print("Terkirim: Ultrasonik=");
    Serial.print(myMessage.ultra_detected ? "DETEKSI" : "AMAN");
    Serial.print(" | ToF=");
    Serial.print(myMessage.tof_detected ? "DETEKSI" : "AMAN");
    Serial.print(" | IMU Heading=");
    Serial.print(myMessage.imu_heading);
    Serial.print(" | HuskyID=");
    Serial.print(myMessage.huskyID);
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


void komunikasiESPNOW(char gerak){
  bool arr[6]; 
  switch(gerak){
    case 'Z': memcpy(arr, (bool[]){0, 0, 0, 0, 0, 0}, sizeof(arr)); break; // siap
    case 'A': memcpy(arr, (bool[]){0, 0, 0, 0, 0, 1}, sizeof(arr)); break; // maju
    case 'B': memcpy(arr, (bool[]){0, 0, 0, 0, 1, 1}, sizeof(arr)); break; // mundur
    case 'C': memcpy(arr, (bool[]){0, 0, 0, 1, 1, 1}, sizeof(arr)); break; // putar kiri
    case 'D': memcpy(arr, (bool[]){0, 0, 1, 1, 1, 1}, sizeof(arr)); break; // putar kanan
    case 'E': memcpy(arr, (bool[]){0, 1, 1, 1, 1, 1}, sizeof(arr)); break; // maju lambat
    case 'F': memcpy(arr, (bool[]){1, 1, 1, 1, 1, 1}, sizeof(arr)); break; // mundur lambat
    case 'G': memcpy(arr, (bool[]){1, 1, 1, 1, 0, 1}, sizeof(arr)); break; // putar kiri lambat
    case 'H': memcpy(arr, (bool[]){1, 1, 1, 0, 0, 1}, sizeof(arr)); break; // putar kanan lambat
    case 'I': memcpy(arr, (bool[]){1, 1, 0, 0, 0, 1}, sizeof(arr)); break; // maju tinggi
    case 'J': memcpy(arr, (bool[]){1, 0, 0, 0, 0, 1}, sizeof(arr)); break; // mundur tinggi
    case 'K': memcpy(arr, (bool[]){1, 1, 1, 1, 1, 0}, sizeof(arr)); break; // putar tinggi kiri
    case 'L': memcpy(arr, (bool[]){1, 1, 1, 1, 0, 0}, sizeof(arr)); break; // putar tinggi kanan
    case 'M': memcpy(arr, (bool[]){1, 1, 1, 0, 0, 0}, sizeof(arr)); break; // maju tinggi lambat
    case 'N': memcpy(arr, (bool[]){1, 1, 0, 0, 0, 0}, sizeof(arr)); break; // mundur tinggi lambat
    case 'O': memcpy(arr, (bool[]){1, 0, 0, 0, 0, 0}, sizeof(arr)); break; // putar tinggi kanan lambat
    case 'P': memcpy(arr, (bool[]){1, 0, 0, 1, 0, 0}, sizeof(arr)); break; // kiri lambat
    case 'Q': memcpy(arr, (bool[]){1, 0, 1, 1, 0, 0}, sizeof(arr)); break; // kanan lambat
    case 'R': memcpy(arr, (bool[]){1, 0, 1, 1, 1, 0}, sizeof(arr)); break; // kiri tinggi
    case 'S': memcpy(arr, (bool[]){1, 0, 1, 1, 1, 1}, sizeof(arr)); break; // kanan tinggi
    case 'T': memcpy(arr, (bool[]){0, 1, 1, 0, 1, 1}, sizeof(arr)); break; // putar tinggi kiri lambat
    case 'U': memcpy(arr, (bool[]){0, 1, 0, 0, 1, 1}, sizeof(arr)); break; // maju tinggi kiri lambat
    case 'V': memcpy(arr, (bool[]){0, 1, 0, 0, 0, 1}, sizeof(arr)); break; // maju tinggi kanan lambat
    case 'W': memcpy(arr, (bool[]){0, 1, 0, 0, 0, 0}, sizeof(arr)); break; // langkah tangga geser kiri
    case 'X': memcpy(arr, (bool[]){0, 0, 1, 1, 0, 0}, sizeof(arr)); break; // langkah tangga geser kanan 
    case 'a': memcpy(arr, (bool[]){1, 1, 0, 0, 1, 1}, sizeof(arr)); break; // capit turun
    case 'b': memcpy(arr, (bool[]){1, 0, 1, 0, 1, 0}, sizeof(arr)); break; // capit naik
    case 'c': memcpy(arr, (bool[]){0, 1, 0, 1, 0, 1}, sizeof(arr)); break; // capit buka
    case 'd': memcpy(arr, (bool[]){1, 1, 1, 0, 0, 0}, sizeof(arr)); break; // capit tutup
    default:
      memcpy(arr, (bool[]){0, 0, 0, 0, 0, 0}, sizeof(arr)); // fallback aman
      Serial.println("Perintah tidak dikenali");
      break;
   }
   memcpy(myMessage.dataPerintah, arr, sizeof(arr));
}

