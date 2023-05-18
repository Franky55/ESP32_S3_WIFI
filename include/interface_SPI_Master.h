
#ifndef INTERFACESPIMASTER_H
#define INTERFACESPIMASTER_H

int interface_SPI_MASTER_initialise();
int interface_SPI_MASTER_Transaction(unsigned char * data, unsigned char * out, unsigned long size);

#endif