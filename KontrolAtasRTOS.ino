//reza aryan gantenk
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

#define ULTRA_DETEKSI_CM 5


// URM09
float ultra1 = 0.0;
float ultra2 = 0.0;

bool ultra1_detected = false;
bool ultra2_detected = false;


// ToF
int distance_tof1 = -1;
int distance_tof2 = -1;
int distance_tof3 = -1;
int distance_tof4 = -1;

bool tof_detected = false;

// IMU
float Roll = 0.0;
float Pitch = 0.0;
float Yaw = 0.0;

int targetSudut = -1;
const int toleransiSudut = 2;   

// Huskylens
float huskyX;
float huskyY;
float huskyWidth;
float huskyHeight;
int huskyID = -1;

// // Deklarasi sensor kamera
// HUSKYLENS huskylens;

// // Deklarasi IMU
// Adafruit_BNO055 bno;

// // Deklarasi sensor URM09 (2 sensor)
// DFRobot_URM09 URM09_1;
// DFRobot_URM09 URM09_2;

// // Deklarasi sensor ToF VL53L0X (4 sensor)
// Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// MAC address Receiver
uint8_t receiverAddress[] = {0x3C, 0x8A, 0x1F, 0xA2, 0x7F, 0x84};

struct_message myMessage;

// pin out led
#define K1 13
#define K2 12
#define K3 11
#define K4 10
#define K5 9

// Deklarasi fungsi setup
void setupHuskylens();
void setupIMUBNO055();
void setupESPNOW();
void setupKomunikasiSerial();
void setupUltraURM09();
void setupToF();

void setPinOutput(bool k1, bool k2, bool k3, bool k4, bool k5);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

// Deklarasi fungsi loop
void loopkirimDataESPNow();
void UltraURM09(void *pvParameters);
void IMUBNO055(void *pvParameters);
void Huskylens(void *pvParameters);
void taskToF(void *pvParameters);

void komunikasiSerial(char gerak);
void komunikasiESPNOW(char gerak);

// Deklarasi task RTOS
void taskToF(void *pvParameters);
void taskUltraURM09(void *pvParameters);
void taskBNO055(void *pvParameters);
void taskHuskyLens(void *pvParameters);

void setup() {
  Serial.begin(115200);

  setupHuskylens();
  setupIMUBNO055();
  setupESPNOW();
  setupKomunikasiSerial();
  setupUltraURM09();
  setupToF();

  setPinOutput(0, 0, 0, 0, 0); 
  // RTOS tasks
  xTaskCreate(taskToF, "ToF", 5000, NULL, 1, NULL);
  xTaskCreate(taskUltraURM09, "UltraURM09", 5000, NULL, 1, NULL);
  xTaskCreate(taskIMUBNO055, "IMUBNO055", 5000, NULL, 1, NULL);
  xTaskCreate(taskHuskylens, "Huskylens", 5000, NULL, 1, NULL);
}


void loop() {

  // perintah (ngarang dulu yeeeee)
  if (ultra1 <= 5 && imu_heading <= 90) {
    komunikasiSerial('S');
    komunikasiESPNOW('S');
  } else if (ultra_detected && tof_detected) {
    komunikasiSerial('B');
    komunikasiESPNOW('B');
  } else if (ultra_detected) {
    komunikasiSerial('B');
    komunikasiESPNOW('B');
  } else if (tof_detected) {
    setPerintahPutarKanan();
    komunikasiSerial('D');
    komunikasiESPNOW('D');
  } else {
    setPerintahMaju();
    komunikasiSerial('A');
    komunikasiESPNOW('A');
  }

  delay(500);  
}
