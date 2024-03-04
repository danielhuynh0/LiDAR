#include <SPI.h>
#include <LoRa.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    // received a paket
    Serial.println("");
    Serial.println("...................................");
    Serial.println("Received packet: ");
    
    // read packet
    while (LoRa.available()) {
      char incoming = (char)LoRa.read();
      Serial.print(incoming);
    }
  }
}
