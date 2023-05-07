#ifndef PROCESSUSCOMMUNICATION_H
#define PROCESSUSCOMMUNICATION_H

typedef struct
{
    unsigned char State;
    unsigned char DataRead;
    unsigned char DataToSend;
}PROCESSUS_WIFI;




int Processus_Communication_initialise(void);

extern PROCESSUS_WIFI processus_WIFI;
#endif