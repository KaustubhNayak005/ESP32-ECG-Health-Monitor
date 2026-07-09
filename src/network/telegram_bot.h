#pragma once
class TelegramNotifier {
public:
    static void init();
    static void sendEmergencyAlert(int hr);
};
