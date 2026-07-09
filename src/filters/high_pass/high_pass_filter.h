#pragma once

class HighPassFilter {
public:
    HighPassFilter(float cutoffFreq, float samplingFreq);
    float process(float input);
    void reset();

private:
    float alpha;
    float prevInput;
    float prevOutput;
    bool isInitialized;
};
