/**
 * @file xinterfaceT1.h
 * @author Francis Gratton
 * @brief pour s'interfacer avec le WIFI. 
 * @version 0.1
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERFACEWIFI_H
#define INTERFACEWIFI_H

//MODULE: interface_WIFI
//DESCRIPTION: pour s'interfacer avec le WIFI. 

//HISTORIQUE:


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de requis

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
int interface_WIFI_initialise();

int interface_WIFI_Connexion();
bool interface_WIFI_Check_Connexion();
int interface_WIFI_Data_Available();
int interface_WIFI_Read(unsigned char * packet, int length);
int interface_WIFI_Send(unsigned char * packet, int length);
void interface_WIFI_Show_Page();
void interface_WIFI_eteint(void);


//Variables publiques:
//pas de variables publiques

#endif