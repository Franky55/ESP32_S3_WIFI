#include <Arduino.h>
#include "main.h"
#include <SPI.h>
#include "interface_SPI.h"


#define MISO 7
#define MOSI 8
#define CLK 6
#define CS1 9

SPIClass interfaceSPI(HSPI);


int interface_SPI_initialise()
{
    interfaceSPI.begin(CLK, MISO, MOSI, CS1);
    //interfaceSPI.setClockDivider(1);
    //interfaceSPI.setDataMode();
    //interfaceSPI.setBitOrder();
    interfaceSPI.setFrequency(10000000);
    return 0;
}


int interface_SPI_Transaction(const unsigned char * data, unsigned char * out, unsigned long size)
{
    interfaceSPI.transferBytes(data, out, size);

    return 0;
}