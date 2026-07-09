#pragma once
class Max30102Sensor {
public:
    static void init();
    static void update();
    static int getHeartRate();
    static int getSpO2();
};
