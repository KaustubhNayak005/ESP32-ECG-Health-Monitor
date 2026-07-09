#include "moving_average_filter.h"

MovingAverageFilter::MovingAverageFilter(float alpha) : alpha(alpha), currentAverage(0.0f), isInitialized(false) {}

float MovingAverageFilter::process(float input) {
    if (!isInitialized) {
        currentAverage = input;
        isInitialized = true;
    } else {
        currentAverage = (alpha * input) + ((1.0f - alpha) * currentAverage);
    }
    return currentAverage;
}

void MovingAverageFilter::reset() {
    currentAverage = 0.0f;
    isInitialized = false;
}
