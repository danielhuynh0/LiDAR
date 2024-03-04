/*
The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <LoRa.h>

VL53L0X sensor;
int distance;

void setup()
{
  delay(5000);
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1)
    {
    }
  }
  // while (!Serial);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  distance = sensor.readRangeContinuousMillimeters();
  Serial.print(distance);
  if (sensor.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }

  Serial.println();

  Serial.println("Sending packet: ");
  LoRa.beginPacket();
  LoRa.print("Distance:");
  LoRa.print(distance);

  LoRa.endPacket();
  Serial.println("Sent!");
  delay(1000);
}
