#include <WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>

const char* ssid = "Batiscan";
const char* password = "BATISCAN";
const IPAddress remoteIP(192, 168, 4, 1);
const int remotePort = 4210;

WiFiUDP udp;
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
const int chipSelectPin = 5; // Pin for SPI chip select (CS)


void setup() {
  Serial.begin(115200);

  SPI.begin();
  pinMode(chipSelectPin, INPUT); // Set the chip select pin as input for SPI slave mode


  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  udp.begin(4210);  // Initialize UDP
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "Hello";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }

  // SPI message receiving code goes here
  while (digitalRead(chipSelectPin) == HIGH) {} // Check if SPI chip select is active low
    char receivedMessage[255];
    int i = 0;
    while (SPI.available()) { // Read bytes until SPI buffer is empty
      receivedMessage[i] = SPI.transfer(0);
      i++;
    }
    receivedMessage[i] = '\0'; // Null-terminate the received message
    Serial.print("Received message via SPI: ");
    Serial.println(receivedMessage);
  

  delay(1000);
}
