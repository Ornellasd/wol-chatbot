#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WakeOnLan.h>
#include "settings.h"

WiFiUDP UDP;
WakeOnLan WOL(UDP);
ESP8266WebServer server(80);

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* MACAddress = MAC_ADDRESS;

void beginWifi();
void beginServer();
void handleRoot();

void beginServer() {
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started.");
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    beginWifi();
    beginServer();
    // 
    Serial.println(MACAddress);
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

void wakeServer() {
    WOL.sendMagicPacket(MACAddress);
}

void handleRoot() {
    server.send(200, "text/plain", "HALLOTJES!, waking server..");
    wakeServer();
}

void loop() {
    server.handleClient();
}