#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WakeOnLan.h>
#include "settings.h"

WiFiUDP UDP;
WakeOnLan WOL(UDP);
ESP8266WebServer server(80);

// String or char here? which is better
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* MACAddress = MAC_ADDRESS;

void beginWifi();
void beginServer();
void handleRoot();
void wakeServer();

// why do some people have "void" in parameter as well?
void setup() {  
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    beginWifi();
    beginServer();
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

void beginServer() {
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started.");
}

void handleRoot() {
    server.send(200, "text/plain", "HALLOTJES!, waking server..");
    wakeServer();
}

void wakeServer() {
    WOL.sendMagicPacket(MACAddress);
}

void loop() {
    server.handleClient();
}