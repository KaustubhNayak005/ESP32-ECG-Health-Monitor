# Hardware Schematic & Wiring Diagram

The following Mermaid diagram illustrates the hardware connections of the **ECG Monitoring System**.

```mermaid
graph TD
    %% Define Components
    ESP[ESP32-WROOM-32]
    AD8232[AD8232 ECG Sensor]
    MAX30102[MAX30102 SpO2 & HR]
    OLED[1.3" OLED Display]
    SD[microSD Card Module]
    BUZ[Active Buzzer]
    PWR[Power Bank 5V]

    %% Wiring connections
    PWR -- 5V --> ESP
    ESP -- 3.3V --> AD8232
    ESP -- 3.3V --> MAX30102
    ESP -- 3.3V --> OLED
    ESP -- 5V --> SD
    
    %% ECG connections
    AD8232 -- OUTPUT --> ESP_ADC[ESP32 GPIO 34]
    AD8232 -- LO+ --> ESP_D14[ESP32 GPIO 14]
    AD8232 -- LO- --> ESP_D12[ESP32 GPIO 12]

    %% I2C connections
    MAX30102 -- SDA --> I2C_SDA[ESP32 GPIO 21]
    MAX30102 -- SCL --> I2C_SCL[ESP32 GPIO 22]
    OLED -- SDA --> I2C_SDA
    OLED -- SCL --> I2C_SCL

    %% SPI connections
    SD -- CS --> SPI_CS[ESP32 GPIO 5]
    SD -- MOSI --> SPI_MOSI[ESP32 GPIO 23]
    SD -- MISO --> SPI_MISO[ESP32 GPIO 19]
    SD -- SCK --> SPI_SCK[ESP32 GPIO 18]

    %% Buzzer connection
    BUZ -- SIGNAL --> ESP_D25[ESP32 GPIO 25]
```
