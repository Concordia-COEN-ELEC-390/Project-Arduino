/*
 * Used to read data from the MQ3 alchohol sensor, and send it to the realtime firebase database.
 * Used with Arduino Nano 33IoT board 
 */
#include <WiFiNINA.h>
#include "Firebase_Arduino_WiFiNINA.h"
#define MQ3pin 0

FirebaseData fbdo;
float sensorValue;                      // variable to store sensor value        
char ssid[] = "Anthony’s iPhone";       // network SSID (name)
char pass[] = "01234567";               // network password (use for WPA, or use as key for WEP)      
int status = WL_IDLE_STATUS;            // Wi-Fi radio's status

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);         // set the LED as output in case we want to use it later

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);    // Connect to WPA/WPA2 network:
    delay(500);                         // retry every 0.5 seconds
  }
  
  Firebase.begin("breathalyzer-app-99c57-default-rtdb.firebaseio.com", "cOcpd8TMsxqYDkMV80SSbasM9lpHxJfmx5Nbtn8A", ssid, pass);
  Firebase.reconnectWiFi(true);

  delay(20000);                         // sensor warmup
}

void loop() {
    
    sensorValue = analogRead(MQ3pin);   // read analog input pin 0
    float bac ((sensorValue - 150) / 1370);                // converts sensor reading up to ~0.5 BAC values

    if (bac < 0.01) {                                         // at this point it's basically 0
      bac = 0.0;
    }
    // try sending data, if not successful then print error 
    if (!(Firebase.setFloat(fbdo, "MQ3 Reading/Value", bac))){
      Serial.println(fbdo.errorReason());
     }

    delay(200);
}
