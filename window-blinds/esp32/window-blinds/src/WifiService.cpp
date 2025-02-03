#include <Arduino.h>
#include <WifiService.h>
#include <WiFi.h>
#include <secrets.h>

WifiService::WifiService() {
    this->wifiMulti = new WiFiMulti();

    wifiMulti->addAP(WIFI_SSID, WIFI_PASSWORD);
}

void WifiService::retryConnectUntilSuccess() {
    Serial.println("Connecting to wifi...");
    while (wifiMulti->run() != WL_CONNECTED){
        delay(100);
    }
    Serial.println("Connected");
    Serial.println(WiFi.localIP());
}

void WifiService::testConnection(int pin) {
    digitalWrite(pin, WiFi.status() == WL_CONNECTED);
}