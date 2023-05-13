#include <Arduino.h>
#include "main.h"
#include <SPI.h>
#include "interface_SPI.h"




SPIClass interfaceSPI(HSPI);


int interface_SPI_initialise()
{
    pinMode(SPI_CS1, OUTPUT);

    digitalWrite(SPI_CS1, LOW);

    interfaceSPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SPI_CS1);
    //interfaceSPI.setClockDivider(1);
    //interfaceSPI.setDataMode();
    //interfaceSPI.setBitOrder();
    // interfaceSPI.setFrequency(10000000);
    return 0;
}


int interface_SPI_Transaction(const unsigned char * data, unsigned char * out, unsigned long size)
{
    interfaceSPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

    digitalWrite(SPI_CS1, LOW);  // Select the slave device
  
  // Send each character of the command string
  for (size_t i = 0; i < size; i++) {
    interfaceSPI.transfer(data[i]);
  }

  digitalWrite(SPI_CS1, HIGH);  // Deselect the slave device
    interfaceSPI.endTransaction();
    Serial.print("Data Sending:     ");

    for(int i = 0; i < size; i++)
    {
        Serial.print((char)data[i]);
    }

    Serial.print("Data Sending:     ");

    for(int i = 0; i < size; i++)
    {
        Serial.print((char)data[i]);
    }


    Serial.print("\nData receiving:     ");

    for(int i = 0; i < size; i++)
    {
        Serial.print((char)out[i]);
    }

    return 0;
}