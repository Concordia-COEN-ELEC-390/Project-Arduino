/*
 * Used to read data from the MQ3 alchohol sensor, and send it to the realtime firebase database.
 * Used with lolin wemos ESP32 board (final design uses this one as it supports a battery)
 */
#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "breathalyzer-app-99c57-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "cOcpd8TMsxqYDkMV80SSbasM9lpHxJfmx5Nbtn8A"
#define WIFI_SSID "BELL078"
#define WIFI_PASSWORD "A56C973DD497"
#define MQ3pin 34

float sensorValue;  // variable to store sensor value

FirebaseData fbdb;

void setup() {
  Serial.begin(115200);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED);

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

  delay(20000);   // sensor warmup
}

void loop() {
    sensorValue = analogRead(MQ3pin); 
    float bac = ((sensorValue - 1150) / 1300);                // converts sensor reading up to ~0.5 BAC values

    if (bac < 0.01) {                                         // at this point it's basically 0
      bac = 0.0;
    }
    
    Firebase.setFloat(fbdb, "MQ3 Reading/Value", bac);
    delay(200);
}
