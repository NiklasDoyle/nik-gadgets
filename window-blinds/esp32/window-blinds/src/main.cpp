#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#include <Stepper.h>
#include <WifiService.h>
#include <secrets.h>

#define MOTOR_INTERFACE_TYPE 1

const int LED_PIN = 2;

const int DIR_PIN = 22;
const int STEP_PIN = 23;

const int MS_PIN_A = 21;
const int MS_PIN_B = 19;
const int MS_PIN_C = 18;

const int SLEEP_PIN = 4;

const int BUTTON_PIN = 15;

const int MS_INC = 3;
const int ROTATIONS = 2;

bool turning = false;
int buttonPress;

Stepper stepper(DIR_PIN, STEP_PIN, MS_PIN_A, MS_PIN_B, MS_PIN_C, SLEEP_PIN, MS_INC);
WifiService wifiService;

AsyncWebServer server(80);

void startTurn() {
  Serial.println("Turning...");
  digitalWrite(SLEEP_PIN, HIGH);
  delay(100);
  turning = true;
}

void endTurn() {
  Serial.println("Done Turning.");
  digitalWrite(SLEEP_PIN, LOW);
}

void setup() {
  Serial.begin(921600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MS_PIN_A, OUTPUT);
  pinMode(MS_PIN_B, OUTPUT);
  pinMode(MS_PIN_C, OUTPUT);

  pinMode(BUTTON_PIN, INPUT);

  //Set Sleep Pin to high
  pinMode(SLEEP_PIN, OUTPUT);
  digitalWrite(SLEEP_PIN, LOW);

  stepper.setRotations(ROTATIONS);

  wifiService.retryConnectUntilSuccess();

  server.on("/rotate", HTTP_GET, [](AsyncWebServerRequest *request){
    startTurn();
    request->send(200, "text/plain", "OK"); });

  server.begin();
}

void loop() {
  buttonPress = digitalRead(BUTTON_PIN);
  wifiService.testConnection(LED_PIN);

  if (buttonPress == HIGH && !turning)
    startTurn();


  if (turning) {
    turning = stepper.run();

    if (!turning)
      endTurn();
  }

}