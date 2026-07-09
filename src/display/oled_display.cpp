#include "oled_display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void OledDisplay::init() {
    if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
    }
}

void OledDisplay::showMessage(const char* msg) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(msg);
    display.display();
}

void OledDisplay::updateData(int hr, int spo2, bool wifiConnected) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("ECG Health Monitor");
    display.print("WiFi: "); display.println(wifiConnected ? "Connected" : "Disc.");
    
    if (hr == 0) {
        display.println("No finger detected.");
    } else {
        display.print("HR: "); display.print(hr); display.println(" BPM");
        display.print("SpO2: "); display.print(spo2); display.println(" %");
    }
    display.display();
}
