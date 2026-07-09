#pragma once
#include "../filters/moving_average/moving_average_filter.h"
#include "../filters/high_pass/high_pass_filter.h"
#include "../filters/low_pass/low_pass_filter.h"
#include "../filters/notch/notch_filter.h"

class EcgSensor {
public:
    static void init();
    static float read();
private:
    static MovingAverageFilter mvFilter;
    static HighPassFilter hpFilter;
    static LowPassFilter lpFilter;
    static NotchFilter notchFilter;
};
