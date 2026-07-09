#include "buzzer.h"
#include "config.h"
#include <Arduino.h>

void Buzzer::init() {
    pinMode(PIN_BUZZER, OUTPUT);
    off();
}
void Buzzer::on() { digitalWrite(PIN_BUZZER, HIGH); }
void Buzzer::off() { digitalWrite(PIN_BUZZER, LOW); }
