#include "sd_logger.h"
#include <SPI.h>
#include <SD.h>
#include "config.h"

static bool ready = false;

void SDLogger::init() {
    if (SD.begin(PIN_SD_CS)) {
        ready = true;
    }
}

void SDLogger::logAlert(int hr, int spo2) {
    if (!ready) return;
    File file = SD.open("/alerts.log", FILE_APPEND);
    if (file) {
        file.print(millis());
        file.print(", HR: "); file.print(hr);
        file.print(", SpO2: "); file.println(spo2);
        file.close();
    }
}
