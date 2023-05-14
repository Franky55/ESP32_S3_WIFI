#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"
//#include "BFIO"
#include <stdio.h>
#include "interface_WIFI.h"
#include "interface_SPI_Master.h"
#include "Processus_Communication.h"

// if udp:         https://gist.github.com/santolucito/70ecb94ce297eb1b8b8034f78683447b



void Processus_Communication_ConnexionClient();
void Processus_Communication_Check_State();
void Processus_Communication_Read();
void Processus_Communication_Send();
void Processus_Communication_SPI();

PROCESSUS_WIFI processus_WIFI;


int compt = 0;



int Processus_Communication_initialise(void)
{
    processus_WIFI.State = 0;
    processus_WIFI.DataToRead = 0;
    processus_WIFI.DataToSend = 0;
    interface_NEOPIXEL_allume(0, 0, 100);
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_ConnexionClient;
    return 0;
}


void Processus_Communication_ConnexionClient()
{
    
    if(interface_WIFI_Connexion() == 0)
    {
        //Serial.println("NOPE");
        processus_WIFI.State = 0;
        return;
    }
    Serial.println("YES");
    //interface_NEOPIXEL_allume(0, 100, 0);
    //interface_WIFI_Show_Page();
    processus_WIFI.State = 1;
 
    //Send hand shake and all my data
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;

}


void Processus_Communication_Check_State()
{
    if(!interface_WIFI_Check_Connexion())
    {
 
        //interface_NEOPIXEL_allume(100, 0, 0);
        processus_WIFI.State = 0;
        processus_WIFI.DataToRead = 0;
        processus_WIFI.DataToSend = 0;
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_ConnexionClient;
        return;
    }

    processus_WIFI.State = 1;

    processus_WIFI.DataToRead = interface_WIFI_Data_Available();
    if(processus_WIFI.DataToRead > 0)
    {

        Serial.println("Data available");

        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Read;
        return;
    }

    if(processus_WIFI.DataToSend == 1)
    {
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Send;
    }


}

void Processus_Communication_Read()
{
    
    int length = interface_WIFI_Read(processus_WIFI.tabReceived, processus_WIFI.DataToRead);
    processus_WIFI.DataToSendSPI = length;
    Serial.print("Processus_Communication_Read: processus_WIFI.tabReceived: ");

    for(int i = 0; i < length; i++)
    {
        Serial.print((char)processus_WIFI.tabReceived[i]);
    }
    Serial.println("");

    if(processus_WIFI.tabReceived[1] == 'N')
    {
        interface_NEOPIXEL_allume(10,10,10);
        //interface_WIFI_eteint();
    }
    if(processus_WIFI.tabReceived[1] == 'F')
    {
        interface_NEOPIXEL_eteint();
        //interface_WIFI_eteint();
    }
    //interface_WIFI_eteint();
    processus_WIFI.DataToRead = 0;//data has been read
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_SPI;

}


void Processus_Communication_Send()
{
    processus_WIFI.DataToSend = 0;//data has been sent
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;

}


void Processus_Communication_SPI()
{
    // compt++;
    // if(compt < 1000)
    // {
    //     return;
    // }
    // compt = 0;
    const unsigned char data[255] = "";
    Serial.println("SPI data sending");
    Serial.print("Processus_Communication_SPI: processus_WIFI.tabReceived: ");

    for(int i = 0; i < processus_WIFI.DataToSendSPI; i++)
    {
        Serial.print((char)processus_WIFI.tabReceived[i]);
    }
    Serial.println("");
    //interface_SPI_Transaction((const unsigned char*)"dat", (unsigned char*)processus_WIFI.tabReceived, 3);
    interface_SPI_MASTER_Transaction((unsigned char*)processus_WIFI.tabReceived, (unsigned char*)data, processus_WIFI.DataToSendSPI);

    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;
}