#pragma once

class LowPassFilter {
public:
    LowPassFilter(float cutoffFreq, float samplingFreq);
    float process(float input);
    void reset();

private:
    float alpha;
    float prevOutput;
    bool isInitialized;
};
