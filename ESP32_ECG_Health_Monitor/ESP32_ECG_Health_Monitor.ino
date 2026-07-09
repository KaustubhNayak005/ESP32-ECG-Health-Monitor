#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "MAX30105.h" // SparkFun MAX3010x library
#include "heartRate.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LittleFS.h>
#include "config.h"

// OLED Display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// MAX30102 settings
MAX30105 particleSensor;
const byte RATE_SIZE = 4; // Increase for more averaging.
byte rates[RATE_SIZE]; // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg = 0;

// Telegram Bot
WiFiClientSecure secured_client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, secured_client);
unsigned long lastTelegramTime = 0;
const unsigned long TELEGRAM_DELAY = 60000; // Only send 1 alert per minute

// Timing for ECG
unsigned long lastEcgTime = 0;
float movingAvgEcg = 0.0;
const float alpha = 0.1; // Smoothing factor for low pass filter

void setup() {
  Serial.begin(115200);
  
  // Initialize Pins
  pinMode(PIN_ECG_LO_PLUS, INPUT);
  pinMode(PIN_ECG_LO_MINUS, INPUT);
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // Initialize LittleFS
  if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
  }

  // Initialize Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
  // Initialize MAX30102
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 was not found. Please check wiring/power.");
  } else {
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0);  // Turn off Green LED
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. ECG Acquisition (250Hz non-blocking)
  if (currentMillis - lastEcgTime >= ECG_SAMPLE_INTERVAL_MS) {
    lastEcgTime = currentMillis;
    
    // Check for leads off
    if ((digitalRead(PIN_ECG_LO_PLUS) == 1) || (digitalRead(PIN_ECG_LO_MINUS) == 1)) {
      // Leads are off, do not log analog signal
      // Serial.println("!"); 
    } else {
      // Read ECG analog value
      int ecgValue = analogRead(PIN_ECG_OUTPUT);
      
      // Basic digital low pass filter (Moving Average)
      movingAvgEcg = (alpha * ecgValue) + ((1.0 - alpha) * movingAvgEcg);
      
      // In a real application, you might plot this via Serial Plotter
      // Serial.println(movingAvgEcg);
    }
  }

  // 2. MAX30102 Heart Rate Reading
  long irValue = particleSensor.getIR();
  
  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
    
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++) {
        beatAvg += rates[x];
      }
      beatAvg /= RATE_SIZE;
    }
  }

  // 3. Update Display (every 500ms)
  static unsigned long lastDisplayTime = 0;
  if (currentMillis - lastDisplayTime > 500) {
    lastDisplayTime = currentMillis;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("ECG Health Monitor");
    display.print("WiFi: ");
    display.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
    
    if (irValue < 50000) {
      display.println("No finger?");
    } else {
      display.print("HR: ");
      display.print(beatAvg);
      display.println(" BPM");
    }
    display.display();
  }
  
  // 4. Alerting & Logging System (Check every few seconds)
  static unsigned long lastAlertCheck = 0;
  if (currentMillis - lastAlertCheck > 5000) {
    lastAlertCheck = currentMillis;
    
    // If heart rate is dangerously high/low and finger is present
    if (irValue > 50000 && (beatAvg > 120 || beatAvg < 40) && beatAvg != 0) {
      if (WiFi.status() == WL_CONNECTED && (currentMillis - lastTelegramTime > TELEGRAM_DELAY)) {
        String message = "EMERGENCY ALERT: Abnormal Heart Rate Detected!\n";
        message += "Current HR: " + String(beatAvg) + " BPM";
        bot.sendMessage(CHAT_ID, message, "");
        lastTelegramTime = currentMillis;
      } else if (WiFi.status() != WL_CONNECTED) {
        // Log to LittleFS for offline storage
        File file = LittleFS.open("/alerts.log", FILE_APPEND);
        if(file){
          file.print(currentMillis);
          file.print(", HR: ");
          file.println(beatAvg);
          file.close();
        }
      }
    }
  }
}
