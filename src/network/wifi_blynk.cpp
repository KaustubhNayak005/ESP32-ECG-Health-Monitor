#include "wifi_blynk.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "config.h"

void WiFiBlynk::init() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Blynk.config(BLYNK_AUTH_TOKEN);
}

void WiFiBlynk::run() {
    Blynk.run();
}

bool WiFiBlynk::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiBlynk::sendECG(float ecg) {
    if (Blynk.connected()) Blynk.virtualWrite(V0, ecg);
}

void WiFiBlynk::sendHealthData(int hr, int spo2) {
    if (Blynk.connected()) {
        Blynk.virtualWrite(V1, hr);
        Blynk.virtualWrite(V2, spo2);
    }
}
