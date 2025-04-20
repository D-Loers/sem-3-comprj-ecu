#include <Arduino.h>
#include "TelematicsECU.hpp"
#include "WiFi.h"
#include "ESP32Ping.h"

const char* SSID = "esp32Network";
const char* PASS = "&61t93K6";
const char* IP = "192.168.137.1";

TelematicsECU* ecu;

void setup() {
    Serial.begin(115200);

    // Connect to wifi
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
    Serial.println("\nConnected");

    // Check connection to server
    Serial.println("Pinging server");
    if (Ping.ping(IP)){
        Serial.println("Ping succesful");
    }else{
        Serial.println("Couldnt communicate to node-red");
        while(1);   // Stop the program from continuing here
    }

    // Setup telematics ECU
    ecu = new TelematicsECU(IP, 50, 5);
    ecu->start();
}

void loop() {
}
