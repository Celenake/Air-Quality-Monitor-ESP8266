#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// --- Couleurs ---
#define ST778X_BLACK 0x0000
#define ST778X_WHITE 0xFFFE
#define ST778X_RED 0x8000
#define ST778X_GREEN 0x007E
#define ST778X_YELLOW 0xFFE0

// --- Connexions SPI ST7789 ---
#define TFT_CS -1 // Pas utilise
#define TFT_DC 5 // GPIO05, D1
#define TFT_RST 2 // GPIO02, D4
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// --- Reseau Wi-Fi ---
const char* ssid = "FRITZinGale2ghz";
const char* password = "ArtistMaksaa+Poulukkah!10a";

IP fixe pour cet ESP ...
IPAddress local_IP(192, 168, 178, 150);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns_server(8, 8, 8, 8);

const char* sensor_ip = "192.168.178.61";

WiFiClient client;
void setup()
{
    Serial.begin(115200);
    // Initialisation ecran
    tft.init(240, 240, SPI_MODE2);
    tft.setRotation(0);
    tft.fillScreen(ST778X_BLACK);
    tft.setTextColor(ST778X_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Connecting WiFi...");
    // Connection Wi-Fi
    WiFi.config(local_IP, gateway, subnet);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    tft.fillScreen(ST778X_BLACK);
    tft.setCursor(10, 10);
    tft.println("Connected!");
    delay(1000);
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String("http://") + sensor_ip + "/data.json";
    http.begin(client, url);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
    float pm25 = -1;
    float pm10 = -1;
    JsonArray values = doc["sensordatavalues"];
    for (JsonObject val : values) {
    const char* type = val["value_type"];
    const char* value = val["value"];
    if (strcmp(type, "SOS_P1") == 0) {
    pm10 = atof(value);
    } else if (strcmp(type, "SOS_P2") == 0) {
    pm25 = atof(value);
    }
    }
    } else {
    // Couleur PM2.5
    uint16_t color_pm25;
    if (pm25 <= 10.0) {
    color_pm25 = ST778X_GREEN;
    } else if (pm25 <= 25.0) {
    color_pm25 = ST778X_YELLOW;
    } else {
    color_pm25 = ST778X_RED;
    }
    }
    uint16_t color_pm10;
    if (pm10 <= 20.0) {
    color_pm10 = ST778X_GREEN;
    } else if (pm10 <= 40.0) {
    color_pm10 = ST778X_YELLOW;
    } else {
    color_pm10 = ST778X_RED;
    }
    // Affichage ecran
    tft.fillScreen(ST778X_BLACK);
    tft.setTextSize(3);
    tft.setCursor(10, 30);
    tft.setTextColor(color_pm25);
    tft.println("PM2.5 (fine): ");
    tft.println(pm25, 1);
    tft.println("ug/m³");
    tft.setTextColor(10, 100);
    tft.setTextSize(2);
    tft.println("COARSE: ");
    tft.println(pm10, 1);
    tft.println("ug/m³");
    } else {
    Serial.println("SON error: ");
    Serial.println(error.c_str());
    }
    } else {
    Serial.println("HTTP error: ");
    Serial.println(httpCode);
    }
    http.end();
} else {
    Serial.println("WiFi not connected.");
}
