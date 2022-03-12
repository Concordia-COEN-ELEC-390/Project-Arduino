/*
 * Used to read data from the MQ3 alchohol sensor, and send it to the realtime firebase database.
 * Used with lolin wemos ESP32 board (final design uses this one as it supports a battery)
 */
#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "breathalyzer-app-99c57-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "cOcpd8TMsxqYDkMV80SSbasM9lpHxJfmx5Nbtn8A"
#define WIFI_SSID "Anthony’s iPhone"
#define WIFI_PASSWORD "01234567"
#define MQ3pin 34

float sensorValue;  // variable to store sensor value

FirebaseData fbdb;

void setup() {
  Serial.begin(115200);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED);

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void loop() {
    sensorValue = analogRead(MQ3pin);
    int val = (sensorValue-1000);                       // this sensor has a really high reading, -1000 brings it about expected (<200 is no alchohol, >~500 is alot)
    Firebase.setFloat(fbdb, "MQ3 Reading/Value", val);
    delay(1000);
}
