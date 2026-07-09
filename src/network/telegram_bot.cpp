#include "telegram_bot.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "config.h"

static WiFiClientSecure secured_client;
static UniversalTelegramBot* bot;
static unsigned long lastTime = 0;

void TelegramNotifier::init() {
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    bot = new UniversalTelegramBot(TELEGRAM_BOT_TOKEN, secured_client);
}

void TelegramNotifier::sendEmergencyAlert(int hr) {
    if (WiFi.status() == WL_CONNECTED && (millis() - lastTime > 60000)) {
        String msg = "EMERGENCY: Abnormal HR Detected! (" + String(hr) + " BPM)";
        bot->sendMessage(CHAT_ID, msg, "");
        lastTime = millis();
    }
}
