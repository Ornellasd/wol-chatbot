#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <WakeOnLan.h>
#include "settings.h"

// String or char here? which is better
// or define like in settings.h?
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* MACAddress = MAC_ADDRESS;

WiFiUDP UDP;
WakeOnLan WOL(UDP);
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// const int ledPin = 2;
// bool ledState = LOW;

void beginWifi();

// why do some people have "void" in parameter as well?
void setup() {  
    Serial.begin(9600);

     #ifdef ESP8266
        configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
        client.setTrustAnchors(&cert);         // Add root certificate for api.telegram.org
    #endif

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

// Telegram Bot functions //
void handleNewMessages(int numNewMesesages) {
    Serial.println("handleNewMessages");
    Serial.println(String(numNewMesesages));

    for (int i=0; i<numNewMesesages; i++) {
        // Chat id of the requester
        String chat_id = String(bot.messages[i].chat_id);

        if (chat_id != CHAT_ID) {
            bot.sendMessage(chat_id, "Unauthorized user", "");
            continue;
        }

        // Print the received message
        String text = bot.messages[i].text;
        Serial.println(text);

        String from_name = bot.messages[i].from_name;

        if (text == "/start") {
            String welcome = "Welcome, " + from_name + ".\n";
            welcome += "Use the following commands to control your ouputs.\n\n";
            welcome += "/wake_server to turn server ON\n";
            welcome += "/sleep_server to turn server OFF\n";
            welcome += "/state to request current state of server\n";
            bot.sendMessage(chat_id, welcome, "");
        }

        if (text == "/wake_server") {
            bot.sendMessage(chat_id, "Waking server", "");
            // WOL.sendMagicPacket(MACAddress);
        }

        if (text == "/state") {
            if (Ping.ping(SERVER_IP_ADDRESS)) {
                bot.sendMessage(chat_id, "Server: BLANK is ON.\n");
            } else {
                bot.sendMessage(chat_id, "Server: BLANK is OFF.\n");
            }
        }
    }

  

}
// END Telegram Bot functions //

void loop() {
    if (millis() > lastTimeBotRan + botRequestDelay) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while(numNewMessages) {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }

        lastTimeBotRan = millis();
    }
}