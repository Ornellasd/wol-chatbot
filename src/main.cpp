#include <ESP8266WiFi.h>

#include "settings.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void beginWifi();

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    beginWifi();
}

void beginWifi() {
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, LOW);
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {

}