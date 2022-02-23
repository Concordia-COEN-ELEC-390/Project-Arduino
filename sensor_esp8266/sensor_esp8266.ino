/*
 * Used to read data from the MQ3 alchohol sensor, and send it to the realtime firebase database.
 * LED flashes until wifi connects.
 * Used with NodeMCU V3 ESP8266 WiFi board 
 */
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "breathalyzer-app-99c57-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "cOcpd8TMsxqYDkMV80SSbasM9lpHxJfmx5Nbtn8A"
#define WIFI_SSID "Anthony’s iPhone"
#define WIFI_PASSWORD "01234567"
#define MQ3pin 0

float sensorValue;  // variable to store sensor value
int ledState = LOW; // ledState used to set the LED

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    // retry every 0.5 
    // toggle LED until connected
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(LED_BUILTIN, ledState);
    delay(500);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
  sensorValue = analogRead(MQ3pin);
  
  // set value
  Firebase.setFloat("MQ3 Reading/Value", sensorValue);
  delay(1000);
}
