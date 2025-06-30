// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// extern int distanceURM1, distanceURM2;
// extern float yaw, pitch, roll;
// extern String kamera;
// extern int tof[4];
// extern String statusKirim;
// extern char perintahAktif;

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// void taskOLED(void *pvParameters) {
//   for (;;) {
//     display.clearDisplay();
//     display.setCursor(0, 0);
//     display.print("U1:"); display.print(distanceURM1); display.print(" U2:"); display.println(distanceURM2);
//     display.print("Y:"); display.print(yaw, 1); display.print(" P:"); display.print(pitch, 1);
//     display.print(" R:"); display.println(roll, 1);
//     display.print("Cam:"); display.println(kamera);
//     display.print("ToF:");
//     for (int i = 0; i < 4; i++) {
//       display.print(tof[i]);
//       if (i < 3) display.print(",");
//     }
//     display.setCursor(0, 48);
//     display.print("Kirim:"); display.print(statusKirim);
//     display.setCursor(80, 48);
//     display.print("Cmd:"); display.print(perintahAktif);
//     display.display();
//     vTaskDelay(pdMS_TO_TICKS(500));
//   }
// }
// void setupOLED(){

// if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//   Serial.println(F("OLED gagal ditemukan"));
//   while (true);
// }
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(0, 0);
//   display.println("Inisialisasi...");
//   display.display();
// }