#pragma once
class EcgSensor {
public:
    static void init();
    static float read();
private:
    static float movingAvgEcg;
};
