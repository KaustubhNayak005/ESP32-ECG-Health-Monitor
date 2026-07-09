<div align="center">
  <img src="https://img.shields.io/badge/PlatformIO-Compatible-orange?style=for-the-badge&logo=PlatformIO" alt="PlatformIO">
  <img src="https://img.shields.io/badge/ESP32-WROOM--32-red?style=for-the-badge&logo=espressif" alt="ESP32">
  <img src="https://img.shields.io/badge/License-Apache_2.0-blue.svg?style=for-the-badge" alt="License">
  <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B" alt="C++">
  <br>
  <h1>ECG Monitoring System with Analog Signal Conditioning</h1>
  <p>A portable, low-cost biomedical monitoring device designed for continuous acquisition, processing, visualization, and remote transmission of physiological signals.</p>
</div>

---

## 📖 Project Overview

Unlike conventional IoT projects that simply interface sensors with a microcontroller, this project emphasizes **analog signal conditioning**, accurate physiological data acquisition, and reliable modular embedded C++ design. 

The ECG signal, which is typically in the range of a few millivolts, is conditioned using the **AD8232 analog front-end** before being digitized by the ESP32. Additional health parameters such as blood oxygen saturation (SpO₂) and heart rate are acquired simultaneously via the **MAX30102**, enabling multi-parameter patient monitoring.

The collected data is displayed locally on an OLED display, transmitted to the cloud via Wi-Fi (Blynk IoT) for remote access, and emergency notifications are sent instantly using a **Telegram Bot**. The system also supports high-speed offline data logging to a **microSD Card** to ensure reliability when network connectivity is unavailable.

---

## 🎯 Objectives

- **Acquire** low-amplitude ECG signals using an analog front-end.
- **Monitor** ECG, Heart Rate, and Blood Oxygen (SpO₂) simultaneously.
- **Visualize** physiological signals in real-time.
- **Enable** wireless remote monitoring over Wi-Fi.
- **Send** emergency alerts through Telegram Bot.
- **Log** data offline via high-speed SPI microSD storage.
- **Build** a low-cost and portable healthcare monitoring device.

---

## 🛠 Hardware Components

| Component | Purpose |
|-----------|---------|
| **ESP32-WROOM-32** | Main microcontroller |
| **AD8232 AFE** | ECG signal acquisition and conditioning |
| **MAX30102** | Heart Rate & SpO₂ Sensor |
| **1.3" OLED** | Local visualization |
| **Active Buzzer** | Emergency audio alerts |
| **microSD Module**| Offline data logging |
| **ECG Electrodes** | Bio-potential acquisition |
| **Power Bank** | Portable 5V power supply |

---

## 🏗 System Architecture

The project has been refactored into a highly modular **PlatformIO** C++ architecture.

```text
ESP32-ECG-Health-Monitor/
├── platformio.ini         (Dependency Management)
├── include/config.h       (Global Settings & Pins)
└── src/
    ├── main.cpp           (Main Loop)
    ├── ecg/               (AD8232 Logic)
    ├── oximeter/          (MAX30102 Logic)
    ├── display/           (OLED Logic)
    ├── storage/           (SD Card Logic)
    ├── network/           (Wi-Fi, Blynk, Telegram Logic)
    └── alerts/            (Buzzer Logic)
```

---

## 🔌 Hardware Schematic & Wiring

The following Mermaid diagram illustrates the exact hardware connections. A separate file is also available in `docs/schematic.md`.

```mermaid
graph TD
    %% Define Components
    ESP[ESP32-WROOM-32]
    AD8232[AD8232 ECG Sensor]
    MAX30102[MAX30102 SpO2 & HR]
    OLED[1.3" OLED Display]
    SD[microSD Card Module]
    BUZ[Active Buzzer]
    PWR[Power Bank 5V]

    %% Wiring connections
    PWR -- 5V --> ESP
    ESP -- 3.3V --> AD8232
    ESP -- 3.3V --> MAX30102
    ESP -- 3.3V --> OLED
    ESP -- 5V --> SD
    
    %% ECG connections
    AD8232 -- OUTPUT --> ESP_ADC[ESP32 GPIO 34]
    AD8232 -- LO+ --> ESP_D14[ESP32 GPIO 14]
    AD8232 -- LO- --> ESP_D12[ESP32 GPIO 12]

    %% I2C connections
    MAX30102 -- SDA --> I2C_SDA[ESP32 GPIO 21]
    MAX30102 -- SCL --> I2C_SCL[ESP32 GPIO 22]
    OLED -- SDA --> I2C_SDA
    OLED -- SCL --> I2C_SCL

    %% SPI connections
    SD -- CS --> SPI_CS[ESP32 GPIO 5]
    SD -- MOSI --> SPI_MOSI[ESP32 GPIO 23]
    SD -- MISO --> SPI_MISO[ESP32 GPIO 19]
    SD -- SCK --> SPI_SCK[ESP32 GPIO 18]

    %% Buzzer connection
    BUZ -- SIGNAL --> ESP_D25[ESP32 GPIO 25]
```

---

## 🚀 Getting Started

This project uses **PlatformIO** for easy compilation and automatic dependency management.

1. **Install PlatformIO**: Install the PlatformIO IDE extension for VS Code.
2. **Clone the Repo**:
   ```bash
   git clone https://github.com/KaustubhNayak005/ESP32-ECG-Health-Monitor.git
   ```
3. **Configure Credentials**: Open `include/config.h` and update your Wi-Fi, Telegram, and Blynk credentials.
4. **Build and Upload**: Click the **Upload** button in PlatformIO. It will automatically download all required libraries (Blynk, Adafruit GFX, MAX30105, TelegramBot) and flash the ESP32.

---

## ⚡ Engineering Challenges & Skills

### Analog Electronics
- **AFE (Analog Front-End)**: Conditioning millivolt-level bio-potentials.
- **Noise Reduction**: Common-mode rejection and high/low-pass filtering.

### Embedded Systems
- **Modular C++**: Distributed, object-oriented firmware architecture.
- **Real-Time Sampling**: Non-blocking 250 Hz ADC acquisition.
- **Peripheral Interfacing**: SPI (SD Card), I2C (OLED, MAX30102), GPIO (Buzzer, Leads-off).

### IoT & Networking
- **Wi-Fi Connectivity**: Asynchronous cloud streaming via Blynk IoT.
- **Telegram APIs**: Secure SSL/TLS connections for emergency Webhook alerts.

---

## 📝 License

This project is licensed under the **Apache License 2.0**. See the [LICENSE](LICENSE) file for more details.

---

## 🔮 Future Enhancements
- Custom ECG Analog Front-End PCB
- Hardware 50 Hz Notch Filter
- AI-based Arrhythmia Detection
- BLE Connectivity & Wearable Form Factor
- Multi-lead ECG Acquisition
