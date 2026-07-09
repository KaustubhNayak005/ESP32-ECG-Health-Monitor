# ESP32 ECG & SpO2 Health Monitor

This project implements an ESP32-WROOM-32 based continuous physiological monitoring system. It reads ECG data using the AD8232 analog front-end at 250 Hz, and Heart Rate / SpO2 data using the MAX30102 sensor. Data is displayed locally on an I2C OLED display, and emergency alerts are sent via a Telegram Bot.

## Features
- **High-Frequency ECG Acquisition**: 250 Hz non-blocking sampling of the AD8232 sensor.
- **Leads-Off Detection**: Built-in hardware checks for LO+ and LO- to detect loose electrodes.
- **Pulse Oximetry**: Integration with MAX30102 for SpO2 and Heart Rate.
- **Local Visualization**: SSD1306 OLED display support via I2C.
- **Offline Data Logging**: LittleFS-based fallback logging when Wi-Fi is disconnected.
- **Telegram Alerts**: Automated notifications for abnormal readings (e.g., HR > 100 or SpO2 < 90%).

## Hardware Setup
- **ESP32-WROOM-32**
- **AD8232 ECG Module**:
  - `OUTPUT` -> `GPIO 34` (Analog IN)
  - `LO+` -> `GPIO 14`
  - `LO-` -> `GPIO 12`
  - `3.3V` -> `3.3V`
  - `GND` -> `GND`
- **MAX30102 Oximeter**:
  - `SDA` -> `GPIO 21`
  - `SCL` -> `GPIO 22`
- **SSD1306 OLED Display**:
  - `SDA` -> `GPIO 21`
  - `SCL` -> `GPIO 22`

## Getting Started

1. Open `ESP32_ECG_Health_Monitor/config.h` and configure:
   - `WIFI_SSID` and `WIFI_PASSWORD`
   - `TELEGRAM_BOT_TOKEN`
   - `CHAT_ID` (Your Telegram user ID)
2. Install the necessary libraries in the Arduino IDE:
   - `SparkFun MAX3010x Pulse and Proximity Sensor Library`
   - `Adafruit SSD1306`
   - `Adafruit GFX Library`
   - `UniversalTelegramBot`
   - `ArduinoJson`
3. Flash the code to your ESP32.

## License
MIT License
