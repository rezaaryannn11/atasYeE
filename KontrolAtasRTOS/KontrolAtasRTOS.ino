#include "Adafruit_VL53L0X.h"
#include "DFRobot_URM09.h"
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <Adafruit_Sensor.h>
#include "HUSKYLENS.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Struktur data untuk pengiriman data via ESP-NOW
typedef struct kirimPesanESPNOW {
    bool dataPerintah[6]; 
} kirimPesanESPNOW;

// ===== Global Variabel Sensor =====

// URM09
float distance_URM09_1 = 0;
// float distance_URM09_2 = 0;

// IMU
float imu_heading = 90;

// ToF
float distance_tof1 = -1;
float distance_tof2 = -1;
float distance_tof3 = -1;
float distance_tof4 = -1;

// IMU
float Roll = 0.0;
float Pitch = 0.0;
float Yaw = 0.0;

int targetSudut = -1;
const int toleransiSudut = 2;   

// Huskylens
int16_t huskyX;
int16_t huskyY;
int16_t huskyWidth;
int16_t huskyHeight;
int16_t huskyID = -1;

// Mutex untuk I2C
SemaphoreHandle_t i2cMutex;

// MAC address Receiver
uint8_t receiverAddress[] = {0x3C, 0x8A, 0x1F, 0xA2, 0x7F, 0x84};
kirimPesanESPNOW myMessage;

// rintangan
bool rintangan_[20] = {false};

// Pin output LED indikator
#define K1 13
#define K2 12
#define K3 11
#define K4 10
#define K5 9

#define SDA_PIN 21
#define SCL_PIN 22

// // Variable LCD Oled
// int distanceURM1 = 0;
// int distanceURM2 = 0;
// float yaw = 0.0, pitch = 0.0, roll = 0.0;
// String kamera = "Target: Tidak";
// int tof[4] = {0, 0, 0, 0};
// String statusKirim = "-";
// char perintahAktif = '-';


// Deklarasi fungsi dari file lain
// void taskToF(void *pvParameters);
void taskURM09(void *pvParameters);
void taskBNO055(void *pvParameters);
// void taskHuskylens(void *pvParameters);
void taskKeputusan(void *pvParameters);
// void taskOLED(void *pvParameters);



// void setupToF();
// void setupUltraURM09();
void setupIMUBNO055();
void setupHuskylens();
// void setupToF();
void setupESPNOW();
// void setPinOutput(bool, bool, bool, bool, bool); // ← deklarasi pin output
// void taskKomunikasiSerial(void *pvParameters);   // ← deklarasi task komunikasi
// void komunikasiSerial(char gerak);   // ← deklarasi komunikasiSerial()
void komunikasiESPNOW(char gerak);   // ← deklarasi untuk kirim perintah ESP-NOW
// void setupOLED();


void setup() {
  Serial.begin(115200);
  delay(200);

  // Inisialisasi I2C dan mutex
  Wire.begin(SDA_PIN, SCL_PIN, 400000);
  i2cMutex = xSemaphoreCreateMutex();

  // Inisialisasi semua sensor dan komunikasi
  setupIMUBNO055();
  setupUltraURM09();
  // setupToF();
  // setupHuskylens();
  setupESPNOW();
  // setupOLED();
  setupKomunikasiSerial();
  setPinOutput(0, 0, 0, 0, 0);

  // Buat RTOS task dan pin ke core aplikasi (1)
  xTaskCreatePinnedToCore(taskURM09,  "URM09",  2048, NULL, 1, NULL, APP_CPU_NUM);
  xTaskCreatePinnedToCore(taskBNO055, "BNO055", 4096, NULL, 1, NULL, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(taskToF, "ToF", 4096, NULL, 1, NULL, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(taskHuskylens, "Huskylens", 5000, NULL, 1, NULL, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(taskKomunikasiSerial, "Serial", 5000, NULL, 1, NULL, 0); 
  xTaskCreatePinnedToCore(taskKeputusan, "Keputusan", 2048, NULL, 1, NULL, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(taskOLED, "Task OLED", 2048, NULL, 1, NULL, 1);

}

void loop() {
  if (!rintangan_[1]) {
      if (distance_URM09_1 <= 5) {
        komunikasiSerial('S');
        Serial.println("[KEPUTUSAN] Kirim perintah: B (Obstacle dekat)");
        rintangan_[1] = true;
      }
    }

    if (!rintangan_[2]) {
      if (distance_URM09_1 >= 30) {
        komunikasiSerial('a');
        Serial.println("[KEPUTUSAN] Kirim perintah: C (Obstacle jauh)");
        rintangan_[2] = true;
      }
    }
}
