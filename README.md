# Air-Quality-Monitor-ESP8266

# Air Quality Monitor with ESP8266

## 📌 Project Description
This project monitors indoor air quality by measuring PM2.5 and PM10 particle concentrations. It uses two ESP8266 (NodeMCU) boards communicating via Wi-Fi:
- **Sensor Node**: Reads data from an SDS011 particle sensor
- **Display Node**: Shows real-time data on an ST7789 color display with color coding

## 🛠️ Hardware Required
| Component | Quantity |
|-----------|----------|
| NodeMCU ESP8266 (or ESP32) | 2 |
| SDS011 Particle Sensor | 1 |
| ST7789 240x240 TFT Display | 1 |
| Jumper wires | Several |
| USB cables | 2 |

## 🔌 Wiring Connections

### Display ESP8266 to ST7789
| ST7789 Pin | ESP8266 Pin |
|------------|-------------|
| VCC | 3.3V |
| GND | GND |
| SCL | D5 (GPIO14) |
| SDA | D7 (GPIO13) |
| DC | D1 (GPIO5) |
| RST | D4 (GPIO2) |
| CS | Not connected (-1) |

### Sensor ESP8266 to SDS011
| SDS011 Pin | ESP8266 Pin |
|------------|-------------|
| TX | D2 (GPIO4) |
| RX | D1 (GPIO5) |
| VCC | 5V |
| GND | GND |

## 📚 Required Libraries
Install these libraries via Arduino IDE (Tools → Manage Libraries):
- `ESP8266WiFi` (built-in with ESP8266 board package)
- `ESP8266HTTPClient` (built-in)
- `ArduinoJson` by Benoit Blanchon
- `Adafruit GFX Library`
- `Adafruit ST7789 Library`

## ⚙️ ESP8266 Board Installation
1. Open Arduino IDE → File → Preferences
2. Add this URL to "Additional Boards Manager URLs":
