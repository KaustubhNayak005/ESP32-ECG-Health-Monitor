#include "ecg_sensor.h"
#include "config.h"

MovingAverageFilter EcgSensor::mvFilter(0.1f);
HighPassFilter EcgSensor::hpFilter(0.5f, 250.0f);
LowPassFilter EcgSensor::lpFilter(40.0f, 250.0f);
NotchFilter EcgSensor::notchFilter(50.0f, 250.0f);

void EcgSensor::init() {
    pinMode(PIN_ECG_LO_PLUS, INPUT);
    pinMode(PIN_ECG_LO_MINUS, INPUT);
}

float EcgSensor::read() {
    if (digitalRead(PIN_ECG_LO_PLUS) == 1 || digitalRead(PIN_ECG_LO_MINUS) == 1) {
        return -1.0; // Leads off
    }
    
    float raw = (float)analogRead(PIN_ECG_OUTPUT);
    
    // Process through filter chain
    float filtered = hpFilter.process(raw);
    filtered = notchFilter.process(filtered);
    filtered = lpFilter.process(filtered);
    filtered = mvFilter.process(filtered);
    
    return filtered;
}
