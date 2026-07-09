#pragma once
class OledDisplay {
public:
    static void init();
    static void showMessage(const char* msg);
    static void updateData(int hr, int spo2, bool wifiConnected);
};
