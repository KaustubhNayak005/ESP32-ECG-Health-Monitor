#include "high_pass_filter.h"
#include <math.h>

HighPassFilter::HighPassFilter(float cutoffFreq, float samplingFreq) {
    float rc = 1.0f / (2.0f * M_PI * cutoffFreq);
    float dt = 1.0f / samplingFreq;
    alpha = rc / (rc + dt);
    reset();
}

float HighPassFilter::process(float input) {
    if (!isInitialized) {
        prevInput = input;
        prevOutput = 0.0f;
        isInitialized = true;
        return 0.0f;
    }

    float output = alpha * (prevOutput + input - prevInput);
    prevInput = input;
    prevOutput = output;
    return output;
}

void HighPassFilter::reset() {
    prevInput = 0.0f;
    prevOutput = 0.0f;
    isInitialized = false;
}
