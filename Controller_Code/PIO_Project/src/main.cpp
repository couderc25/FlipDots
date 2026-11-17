#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

const int datapin = 15;
const int clockpin = 4;
const int latchpin = 2;

const char* ssid = "TP-Link_A378";
const char* password = "3mQ5amU3";

byte data = 0;

// Write the entire byte to the shift register
void writeOutputs(byte value)
{
    data = value;

    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, data);
    digitalWrite(latchpin, HIGH);
}

void setup()
{
    Serial.begin(115200);

    pinMode(datapin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    pinMode(latchpin, OUTPUT);

    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Start OTA
    ArduinoOTA.begin();
}

void loop()
{
    ArduinoOTA.handle();

    // Move two LEDs together from left to right
    for (int i = 0; i < 7; i++)
    {
        byte pattern = (1 << i) | (1 << (i + 1));
        writeOutputs(pattern);

        delay(400);
        ArduinoOTA.handle();
    }

    // Move two LEDs together from right to left
    for (int i = 6; i >= 0; i--)
    {
        byte pattern = (1 << i) | (1 << (i + 1));
        writeOutputs(pattern);

        delay(400);
        ArduinoOTA.handle();
    }
}