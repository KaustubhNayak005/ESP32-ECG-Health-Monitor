#ifndef CONFIG_H
#define CONFIG_H

// -----------------------------------------
// Wi-Fi & Blynk Configuration
// -----------------------------------------
#define BLYNK_TEMPLATE_ID   "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "ECG Monitor"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

#define WIFI_SSID           "YOUR_WIFI_SSID"
#define WIFI_PASSWORD       "YOUR_WIFI_PASSWORD"

// -----------------------------------------
// Telegram Bot Configuration
// -----------------------------------------
#define TELEGRAM_BOT_TOKEN  "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID             "YOUR_CHAT_ID"

// -----------------------------------------
// Pin Definitions
// -----------------------------------------
// AD8232 ECG Sensor
#define PIN_ECG_OUTPUT      34  // Analog Input
#define PIN_ECG_LO_PLUS     14  // Leads Off +
#define PIN_ECG_LO_MINUS    12  // Leads Off -

// I2C Pins for MAX30102 & OLED (ESP32 defaults)
// SDA = 21, SCL = 22

// SPI Pins for microSD Card (ESP32 defaults)
#define PIN_SD_CS           5
// MOSI = 23, MISO = 19, SCK = 18

// Buzzer
#define PIN_BUZZER          25

// -----------------------------------------
// System Configuration
// -----------------------------------------
#define ECG_SAMPLE_RATE_HZ     250
#define ECG_SAMPLE_INTERVAL_MS (1000 / ECG_SAMPLE_RATE_HZ)

#endif // CONFIG_H
