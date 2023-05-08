
#ifndef INTERFACESPI_H
#define INTERFACESPI_H

int interface_SPI_initialise();
int interface_SPI_Transaction(const unsigned char * data, unsigned char * out, unsigned long size);

#endif