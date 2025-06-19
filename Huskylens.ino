// Deklarasi sensor kamera
HUSKYLENS huskylens;

void setupHuskylens (){
// Inisialisasi HuskyLens
  if (!huskylens.begin(Wire)) {
    Serial.println("HUSKYLENS not connected. Check wiring.");
    while (1); 
  }

  Serial.println("HUSKYLENS initialized");
}

void taskHuskylens(void *pvParameters) {
  while (true) {
    if (!huskylens.request()) {
      Serial.println(F("Gagal meminta data dari HUSKYLENS. Periksa koneksi!"));
      huskyID = -1;
    } else if (!huskylens.isLearned()) {
      Serial.println(F("Belum ada objek yang dipelajari. Tekan tombol Learn di HUSKYLENS!"));
      huskyID = -1;
    } else if (!huskylens.available()) {
      Serial.println(F("Tidak ada blok/objek yang muncul di layar!"));
      huskyID = -1;
    } else {
      Serial.println(F("###########"));
      while (huskylens.available()) {
        HUSKYLENSResult result = huskylens.read();

        if (result.command == COMMAND_RETURN_BLOCK) {
          
          // Simpan ke variabel global
          huskyX = result.xCenter;
          huskyY = result.yCenter;
          huskyWidth = result.width;
          huskyHeight = result.height;
          huskyID = result.ID;

          // Hasil
          Serial.println(String() + F("Block: xCenter=") + huskyX +
                         F(", yCenter=") + huskyY +
                         F(", width=") + huskyWidth +
                         F(", height=") + huskyHeight +
                         F(", ID=") + huskyID);

          if (huskyID == 1) {
            Serial.println(F("Korban terdeteksi"));
          }
        } else {
          Serial.println("Objek tidak dikenali!");
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(200));
  }
}





