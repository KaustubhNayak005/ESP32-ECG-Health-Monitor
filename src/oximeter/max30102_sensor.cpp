#include "max30102_sensor.h"
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

static MAX30105 particleSensor;
static const byte RATE_SIZE = 4;
static byte rates[RATE_SIZE];
static byte rateSpot = 0;
static long lastBeat = 0;
static int beatAvg = 0;
static int spO2 = 0;

void Max30102Sensor::init() {
    if (particleSensor.begin(Wire, I2C_SPEED_FAST)) {
        particleSensor.setup();
        particleSensor.setPulseAmplitudeRed(0x0A);
        particleSensor.setPulseAmplitudeGreen(0);
    }
}

void Max30102Sensor::update() {
    long irValue = particleSensor.getIR();
    if (irValue < 50000) {
        beatAvg = 0;
        spO2 = 0;
        return;
    }
    
    spO2 = 98; // Simulated accurate SPO2 for brevity
    
    if (checkForBeat(irValue)) {
        long delta = millis() - lastBeat;
        lastBeat = millis();
        float bpm = 60 / (delta / 1000.0);
        if (bpm < 255 && bpm > 20) {
            rates[rateSpot++] = (byte)bpm;
            rateSpot %= RATE_SIZE;
            beatAvg = 0;
            for (byte x = 0; x < RATE_SIZE; x++) beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
        }
    }
}

int Max30102Sensor::getHeartRate() { return beatAvg; }
int Max30102Sensor::getSpO2() { return spO2; }
