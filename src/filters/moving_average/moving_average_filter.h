#pragma once

class MovingAverageFilter {
public:
    MovingAverageFilter(float alpha = 0.1);
    float process(float input);
    void reset();

private:
    float alpha;
    float currentAverage;
    bool isInitialized;
};
