# Wireless-Level-Monitoring-System-Using-Ultrasonic-Sensor


### Introduction
The Wireless Ultrasonic Level Monitor is a project designed to measure and display the level and volume of liquids in a container, such as water in a tank. The system consists of a transmitter unit with an ultrasonic sensor and an RF module, and a receiver unit with an OLED display and RF module. This can be used in both home and industrial settings for efficient water management.

### Components
- **Transmitter Unit:**
  - Arduino Uno
  - HC-SR04 Ultrasonic Sensor
  - NRF24L01 RF Transmitter

- **Receiver Unit:**
  - Arduino Uno
  - 4-pin OLED Display
  - NRF24L01 RF Receiver

### Connections

#### Transmitter Unit

| NRF24L01     | Arduino |
|--------------|---------|
| GND          | GND     |
| VCC          | 3.3V    |
| CE           | D9      |
| CSN          | D10     |
| SCK          | D13     |
| MOSI         | D11     |
| MISO         | D12     |

| HC-SR04      | Arduino |
|--------------|---------|
| VCC          | 5V      |
| Trig         | D7      |
| Echo         | D8      |
| GND          | GND     |

#### Receiver Unit

| NRF24L01     | Arduino |
|--------------|---------|
| GND          | GND     |
| VCC          | 3.3V    |
| CE           | D7      |
| CSN          | D8      |
| SCK          | D13     |
| MOSI         | D11     |
| MISO         | D12     |

| OLED Display | Arduino |
|--------------|---------|
| GND          | GND     |
| VCC          | 5V      |
| SCK          | A5      |
| SDA          | A4      |

This project provides an effective solution for monitoring and managing liquid levels, ensuring accurate measurements and an easy-to-read display.

---
