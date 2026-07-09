# ECG Monitoring System with Analog Signal Conditioning

---

## Project Overview

The **ECG Monitoring System with Analog Signal Conditioning** is a portable, low-cost biomedical monitoring device designed for continuous acquisition, processing, visualization, and remote transmission of physiological signals. The system combines an **analog ECG acquisition front-end**, embedded processing, wireless communication, and cloud connectivity to provide real-time health monitoring.

Unlike conventional IoT projects that simply interface sensors with a microcontroller, this project emphasizes **analog signal conditioning**, accurate physiological data acquisition, and reliable embedded system design. The ECG signal, which is typically in the range of a few millivolts, is conditioned using a dedicated analog front-end before being digitized by the ESP32. Additional health parameters such as blood oxygen saturation (SpO₂) and heart rate are acquired simultaneously, enabling multi-parameter patient monitoring.

The collected data is displayed locally on an OLED display, transmitted to the cloud via Wi-Fi for remote access, and emergency notifications are sent instantly using a Telegram Bot. The system also supports offline data logging to ensure reliability when network connectivity is unavailable.

---

# Objectives

- Acquire low-amplitude ECG signals using an analog front-end.
- Monitor ECG, Heart Rate, and Blood Oxygen (SpO₂) simultaneously.
- Provide real-time visualization of physiological signals.
- Enable wireless remote monitoring over Wi-Fi.
- Send emergency alerts through Telegram Bot.
- Support offline data logging.
- Build a low-cost and portable healthcare monitoring device.

---

# Hardware Components

| Component | Purpose |
|-----------|---------|
| ESP32-WROOM-32 | Main microcontroller |
| AD8232 ECG Analog Front-End | ECG signal acquisition and conditioning |
| MAX30102 | Heart Rate & SpO₂ Sensor |
| 1.3" OLED Display | Local visualization |
| Buzzer | Emergency alerts |
| microSD Card Module | Offline data logging |
| ECG Electrodes | Bio-potential acquisition |
| Power Bank | Portable power supply |

---

# Communication Interfaces

## ADC
Used for:
- ECG signal acquisition
- Sampling conditioned analog output from AD8232
- 250 Hz sampling rate

## I²C
Used for:
- MAX30102
- OLED Display

Advantages:
- Two-wire communication
- Low pin count
- Multiple devices on same bus

## SPI
Used for:
- microSD Card

Advantages:
- High-speed data logging
- Reliable storage

## GPIO
Used for:
- Buzzer
- Status LEDs
- Control signals

## Wi-Fi
ESP32 onboard Wi-Fi is used for:
- Cloud communication
- Remote monitoring
- IoT dashboard
- Telegram Bot communication

---

# Analog Signal Conditioning

The analog section is the core of the project.
The AD8232 Analog Front-End performs:
- Instrumentation amplification
- Common-mode noise rejection
- High-pass filtering
- Low-pass filtering
- Baseline stabilization
- Motion artifact reduction

The conditioned ECG signal is then fed to the ESP32 ADC for digitization.

---

# Software Stack

- Embedded C++
- Arduino Framework
- ESP32 SDK
- Wi-Fi Networking
- Telegram Bot API
- Blynk IoT Platform
- OLED Graphics Library
- MAX30102 Driver
- ADC Driver

---

# System Architecture

```
ECG Electrodes
        │
        ▼
 AD8232 Analog Front-End
        │
        ▼
     ESP32 ADC
        │
        ▼
 Signal Processing
        │
 ┌──────┼─────────────┐
 │      │             │
 ▼      ▼             ▼
OLED  Cloud      Telegram Bot
(I²C) (Wi-Fi)     Alerts
        │
        ▼
 Offline Storage
   (SPI microSD)
```

---

# Key Features

- Analog ECG signal conditioning
- Real-time ECG acquisition (250 Hz)
- Continuous Heart Rate Monitoring
- Blood Oxygen (SpO₂) Measurement
- OLED real-time display
- Wi-Fi enabled cloud monitoring
- Telegram emergency notifications
- Offline data logging
- Portable battery-powered design
- Low-cost implementation

---

# Engineering Challenges

## Analog
- Acquiring millivolt-level ECG signals
- Reducing motion artifacts
- Minimizing electrical noise
- Stable ADC sampling

## Embedded
- Simultaneous sensor interfacing
- Real-time sampling
- Display updates
- Cloud communication
- Data logging

## Communication
- Wi-Fi connectivity
- Telegram API integration
- Cloud synchronization

---

# Skills Demonstrated

## Analog Electronics
- Analog Front-End (AFE)
- Signal Conditioning
- Biomedical Signal Acquisition
- Noise Reduction
- ADC Interfacing

## Embedded Systems
- ESP32 Firmware Development
- Interrupt Handling
- Real-Time Sampling
- Peripheral Drivers
- Embedded C++

## Communication Protocols
- ADC
- I²C
- SPI
- GPIO
- Wi-Fi
- HTTP/API Communication

## IoT
- Cloud Monitoring
- Remote Healthcare
- Telegram Bot Integration
- Real-Time Alerts

## Biomedical Engineering
- ECG Acquisition
- Heart Rate Monitoring
- Blood Oxygen Measurement
- Portable Patient Monitoring

---

# Resume Description

### ECG Monitoring System with Analog Signal Conditioning
- Developed an **ESP32-WROOM-32** based ECG monitoring system using the **AD8232 analog front-end**, **MAX30102** (SpO₂ & Heart Rate), and **OLED (I²C)** for real-time physiological monitoring.
- Implemented **250 Hz** ECG acquisition, **Wi-Fi**-based cloud monitoring, **Telegram Bot API** alerts, and peripheral interfacing via **ADC**, **I²C**, **SPI**, and **GPIO** for continuous remote healthcare monitoring and offline data logging.
- Improved signal reliability through analog signal conditioning and real-time processing while enabling portable, low-cost patient monitoring.

---

# Technologies Used

### Hardware
- ESP32-WROOM-32
- AD8232
- MAX30102
- OLED Display
- microSD Card
- Buzzer

### Protocols
- ADC
- I²C
- SPI
- GPIO
- Wi-Fi

### Software
- Embedded C++
- Arduino IDE
- Blynk IoT
- Telegram Bot API

---

# Interview Topics Covered

## Analog Electronics
- Analog Signal Conditioning
- Instrumentation Amplifiers
- ECG Acquisition
- Noise Reduction
- Biomedical Sensors
- ADC Sampling

## Embedded Systems
- ESP32
- Interrupts
- Peripheral Interfacing
- Memory Management
- Real-Time Systems

## Communication
- I²C
- SPI
- GPIO
- Wi-Fi
- REST APIs
- Telegram Bot API

## IoT
- Cloud Monitoring
- Remote Healthcare
- Real-Time Alerts

## Biomedical
- ECG Signal Acquisition
- Heart Rate Detection
- SpO₂ Monitoring
- Portable Medical Devices

---

# Possible Future Enhancements

- Custom ECG Analog Front-End PCB
- Hardware 50 Hz Notch Filter
- Anti-Aliasing Filter Design
- AI-based Arrhythmia Detection
- BLE Connectivity
- Mobile Application
- Wearable Form Factor
- Secure Cloud Communication (TLS)
- Battery Management System
- Low-Power Optimization
- Multi-lead ECG Acquisition
