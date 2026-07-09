#include <Arduino.h>
#include "config.h"
#include "ecg/ecg_sensor.h"
#include "oximeter/max30102_sensor.h"
#include "display/oled_display.h"
#include "storage/sd_logger.h"
#include "network/wifi_blynk.h"
#include "network/telegram_bot.h"
#include "alerts/buzzer.h"

unsigned long lastEcgTime = 0;
unsigned long lastDisplayTime = 0;
unsigned long lastAlertCheck = 0;

void setup() {
    Serial.begin(115200);
    Buzzer::init();
    OledDisplay::init();
    OledDisplay::showMessage("Initializing...");
    
    SDLogger::init();
    WiFiBlynk::init();
    TelegramNotifier::init();
    Max30102Sensor::init();
    EcgSensor::init();
    
    OledDisplay::showMessage("System Ready");
}

void loop() {
    unsigned long currentMillis = millis();
    WiFiBlynk::run();

    // 1. ECG Acquisition (250 Hz)
    if (currentMillis - lastEcgTime >= ECG_SAMPLE_INTERVAL_MS) {
        lastEcgTime = currentMillis;
        float ecgValue = EcgSensor::read();
        if (ecgValue >= 0) { // Valid reading
            WiFiBlynk::sendECG(ecgValue);
        }
    }

    // 2. Heart Rate & SpO2
    Max30102Sensor::update();

    // 3. Update Display
    if (currentMillis - lastDisplayTime > 500) {
        lastDisplayTime = currentMillis;
        int hr = Max30102Sensor::getHeartRate();
        int spo2 = Max30102Sensor::getSpO2();
        OledDisplay::updateData(hr, spo2, WiFiBlynk::isConnected());
        WiFiBlynk::sendHealthData(hr, spo2);
    }

    // 4. Alerts & Logging
    if (currentMillis - lastAlertCheck > 5000) {
        lastAlertCheck = currentMillis;
        int hr = Max30102Sensor::getHeartRate();
        
        if (hr > 120 || (hr < 40 && hr > 0)) {
            Buzzer::on();
            TelegramNotifier::sendEmergencyAlert(hr);
            SDLogger::logAlert(hr, Max30102Sensor::getSpO2());
        } else {
            Buzzer::off();
        }
    }
}
