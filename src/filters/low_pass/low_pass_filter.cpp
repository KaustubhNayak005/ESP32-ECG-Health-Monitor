#include "low_pass_filter.h"
#include <math.h>

LowPassFilter::LowPassFilter(float cutoffFreq, float samplingFreq) {
    float rc = 1.0f / (2.0f * M_PI * cutoffFreq);
    float dt = 1.0f / samplingFreq;
    alpha = dt / (rc + dt);
    reset();
}

float LowPassFilter::process(float input) {
    if (!isInitialized) {
        prevOutput = input;
        isInitialized = true;
        return input;
    }

    float output = (alpha * input) + ((1.0f - alpha) * prevOutput);
    prevOutput = output;
    return output;
}

void LowPassFilter::reset() {
    prevOutput = 0.0f;
    isInitialized = false;
}
