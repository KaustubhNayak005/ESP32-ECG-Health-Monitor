#pragma once
#include <Arduino.h>

// Wi-Fi & Blynk
#define BLYNK_TEMPLATE_ID   "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "ECG Monitor"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"
#define WIFI_SSID           "YOUR_WIFI_SSID"
#define WIFI_PASSWORD       "YOUR_WIFI_PASSWORD"

// Telegram
#define TELEGRAM_BOT_TOKEN  "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID             "YOUR_CHAT_ID"

// Pins
#define PIN_ECG_OUTPUT      34
#define PIN_ECG_LO_PLUS     14
#define PIN_ECG_LO_MINUS    12
#define PIN_SD_CS           5
#define PIN_BUZZER          25

// ECG Settings
#define ECG_SAMPLE_RATE_HZ     250
#define ECG_SAMPLE_INTERVAL_MS (1000 / ECG_SAMPLE_RATE_HZ)
