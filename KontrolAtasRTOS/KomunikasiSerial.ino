void setPinOutput(bool k1, bool k2, bool k3, bool k4, bool k5) {
  digitalWrite(K1, k1);
  digitalWrite(K2, k2);
  digitalWrite(K3, k3);
  digitalWrite(K4, k4);
  digitalWrite(K5, k5);
}

void setupKomunikasiSerial() {
  // Inisialisasi pin sebagai OUTPUT
  pinMode(K1, OUTPUT);
  pinMode(K2, OUTPUT);
  pinMode(K3, OUTPUT);
  pinMode(K4, OUTPUT);
  pinMode(K5, OUTPUT);

  // Set awal semua LOW
  setPinOutput(0, 0, 0, 0, 0);
  Serial.println("[KOMUNIKASI SERIAL] Inisialisasi pin K1–K5 selesai");
}

void komunikasiSerial(char gerak){
  switch(gerak){
    case 'S': setPinOutput(0, 0, 0, 0, 0); break; // siap
    case 'a': setPinOutput(1, 1, 1, 1, 0); break; // maju
    case 'b': setPinOutput(1, 1, 1, 0, 1); break; // mundur
    case 'c': setPinOutput(1, 1, 1, 0, 0); break; // putar_kiri
    case 'd': setPinOutput(1, 1, 0, 1, 1); break; // putar_kanan
    case 'e': setPinOutput(1, 1, 0, 1, 0); break; // maju_lambat
    case 'f': setPinOutput(1, 1, 0, 0, 1); break; // mundur_lambat
    case 'g': setPinOutput(1, 1, 0, 0, 0); break; // putar_kiri_lambat
    case 'h': setPinOutput(1, 0, 1, 1, 1); break; // putar_kanan_lambat
    case 'i': setPinOutput(1, 0, 1, 1, 0); break; // maju_tinggi
    case 'j': setPinOutput(1, 0, 1, 0, 1); break; // mundur_tinggi
    case 'k': setPinOutput(1, 0, 1, 0, 0); break; // putar_tinggi_kiri
    case 'l': setPinOutput(1, 0, 0, 1, 1); break; // putar_tinggi_kanan
    case 'm': setPinOutput(1, 0, 0, 1, 0); break; // maju_tinggi_lambat
    case 'n': setPinOutput(1, 0, 0, 0, 1); break; // mundur_tinggi_lambat
    case 'o': setPinOutput(0, 1, 1, 1, 1); break; // putar_tinggi_kanan_lambat
    case 'p': setPinOutput(0, 1, 1, 1, 0); break; // kiri_lambat
    case 'q': setPinOutput(0, 1, 1, 0, 1); break; // kanan_lambat
    case 'r': setPinOutput(0, 1, 1, 0, 0); break; // kiri_tinggi
    case 's': setPinOutput(0, 1, 0, 1, 1); break; // kanan_tinggi
    case 't': setPinOutput(0, 1, 0, 1, 0); break; // putar_tinggi_kiri_lambat
    case 'u': setPinOutput(0, 1, 0, 0, 1); break; // maju_tinggi_kiri_lambat
    case 'v': setPinOutput(0, 1, 0, 0, 0); break; // maju_tinggi_kanan_lambat
    case 'w': setPinOutput(0, 0, 1, 1, 1); break; // langkah_tangga_geser_kiri
    case 'x': setPinOutput(0, 0, 1, 1, 0); break; // langkah_tangga_geser_kanan
    case 'A': setPinOutput(0, 0, 0, 1, 1); break; // capit_turun
    case 'B': setPinOutput(0, 0, 0, 1, 0); break; // capit_naik
    case 'C': setPinOutput(0, 0, 0, 0, 1); break; // capit_buka
    case 'D': setPinOutput(1, 1, 1, 1, 1); break; // capit_tutup
    default:
      Serial.println("Perintah tidak dikenal!");
      setPinOutput(0, 0, 0, 0, 0); // fallback aman
      break;
  }
}