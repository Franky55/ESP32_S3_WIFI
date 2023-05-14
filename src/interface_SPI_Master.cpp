#include <Arduino.h>
#include "main.h"
#include <SPI.h>
#include "interface_SPI_Master.h"




SPIClass interfaceSPI_Master(HSPI);


int interface_SPI_MASTER_initialise()
{
    pinMode(SPI_CS1, OUTPUT);

    digitalWrite(SPI_CS1, LOW);

    interfaceSPI_Master.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SPI_CS1);
    //interfaceSPI_Master.setClockDivider(1);
    //interfaceSPI_Master.setDataMode();
    //interfaceSPI_Master.setBitOrder();
    // interfaceSPI_Master.setFrequency(10000000);
    return 0;
}


int interface_SPI_MASTER_Transaction(unsigned char * data, unsigned char * out, unsigned long size)
{
    interfaceSPI_Master.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

    digitalWrite(SPI_CS1, LOW);  // Select the slave device
  
  // Send each character of the command string
  for (size_t i = 0; i < size; i++) {
    interfaceSPI_Master.transfer(data[i]);
  }

  digitalWrite(SPI_CS1, HIGH);  // Deselect the slave device
    interfaceSPI_Master.endTransaction();
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