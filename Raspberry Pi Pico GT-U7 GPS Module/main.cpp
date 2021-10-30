#include <Arduino.h>
#include "TinyGPS++.h"

TinyGPSPlus gps;        /* Instantiate GPS object */
int gpsBaudRate = 9600; /* Default baud rate */

/* GPS RX to Pico UART1 TX, GPS TX to Pico UART1 RX */
/* Open GPIO Pin 8 and Pin 9 for Serial2 communication (UART0 = Serial1, UART1 = Serial2) */
UART Serial2(8,9,0,0); 

/* Friends of Amateur Rocketry launch site coordinates */
double launchSiteLatitude = 35.34678489;
double launchSiteLongitude = -117.80820611;

void setup() {
  Serial.begin(115200); /* Opens serial monitor port */
  Serial2.begin(gpsBaudRate); /* Opens Serial2 communication port */
  Serial.println("GPS Module starting.");
}

void loop() {
  /* Feed received GPS NMEA data into GPS object for encoding */
  if (Serial2.available()) {
    gps.encode(Serial2.read());
  }

  /* Print GPS encoded data if location is updated */
  if(gps.location.isUpdated()) {
    Serial.print("Date:");
    Serial.print(gps.date.value());
    Serial.print(" | UTC:");
    Serial.print(gps.time.value());
    Serial.print(" | Satellites:");
    Serial.print(gps.satellites.value());
    Serial.print(" | Lat:");
    Serial.print(gps.location.lat(), 8);
    Serial.print(" | Long:");
    Serial.print(gps.location.lng(), 8);
    Serial.print(" | Speed:");
    Serial.print(gps.speed.mps());
    Serial.print("m/s");
    Serial.print(" | Altitude:");
    Serial.print(gps.altitude.meters());
    Serial.print("m");
    Serial.print(" | Distance:");
    Serial.print(gps.distanceBetween(gps.location.lat(),gps.location.lng(),launchSiteLatitude,launchSiteLongitude));
    Serial.println("m");
  }
}