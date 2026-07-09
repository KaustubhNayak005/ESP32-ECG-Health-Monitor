#pragma once
class WiFiBlynk {
public:
    static void init();
    static void run();
    static bool isConnected();
    static void sendECG(float ecg);
    static void sendHealthData(int hr, int spo2);
};
