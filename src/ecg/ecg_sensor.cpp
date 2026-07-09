#include "ecg_sensor.h"
#include "config.h"

float EcgSensor::movingAvgEcg = 0.0;

void EcgSensor::init() {
    pinMode(PIN_ECG_LO_PLUS, INPUT);
    pinMode(PIN_ECG_LO_MINUS, INPUT);
}

float EcgSensor::read() {
    if (digitalRead(PIN_ECG_LO_PLUS) == 1 || digitalRead(PIN_ECG_LO_MINUS) == 1) {
        return -1.0; // Leads off
    }
    int raw = analogRead(PIN_ECG_OUTPUT);
    const float alpha = 0.1;
    movingAvgEcg = (alpha * raw) + ((1.0 - alpha) * movingAvgEcg);
    return movingAvgEcg;
}
