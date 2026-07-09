#include "notch_filter.h"
#include <math.h>

NotchFilter::NotchFilter(float centerFreq, float samplingFreq, float qFactor) {
    float omega = 2.0f * M_PI * centerFreq / samplingFreq;
    float alpha = sin(omega) / (2.0f * qFactor);
    
    float a0 = 1.0f + alpha;
    
    b0 = 1.0f / a0;
    b1 = -2.0f * cos(omega) / a0;
    b2 = 1.0f / a0;
    a1 = -2.0f * cos(omega) / a0;
    a2 = (1.0f - alpha) / a0;
    
    reset();
}

float NotchFilter::process(float input) {
    if (!isInitialized) {
        x1 = x2 = input;
        y1 = y2 = input;
        isInitialized = true;
        return input;
    }

    float output = b0 * input + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
    
    x2 = x1;
    x1 = input;
    
    y2 = y1;
    y1 = output;
    
    return output;
}

void NotchFilter::reset() {
    x1 = x2 = 0.0f;
    y1 = y2 = 0.0f;
    isInitialized = false;
}
