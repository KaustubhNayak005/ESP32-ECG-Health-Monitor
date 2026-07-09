#pragma once

class NotchFilter {
public:
    NotchFilter(float centerFreq, float samplingFreq, float qFactor = 30.0f);
    float process(float input);
    void reset();

private:
    float b0, b1, b2;
    float a1, a2;
    
    float x1, x2;
    float y1, y2;
    
    bool isInitialized;
};
