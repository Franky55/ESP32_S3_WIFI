
#include "main.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "interface_WIFI.h"

WiFiServer server(80);
WiFiClient client;


/**
 * @brief Initialisation du serveur
 * N'importe qui peut se connecter au serveur avec le bon mot de passe
 * 
 * @return int 
 */
int interface_WIFI_initialise()
{
    // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
    log_e("Soft AP creation failed.");
    return -1;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");

  return 0;
}


/**
 * @brief La fonction retourne 0 jusqu'à ce qu'un
 * client se connecte au serveur
 * 
 * @return int 
 */
int interface_WIFI_Connexion()
{
    client = server.available();   // listen for incoming clients

    if (client) 
    {
        return 1;
    }

    return 0;
}

/**
 * @brief La fonction retourne true s'il y a du 
 * data a lire
 * 
 * @return true 
 * @return false 
 */
bool interface_WIFI_Data_Available()
{
    return client.available();
}


/**
 * @brief 
 * La fonction retourne true si le client est encore connecté
 * La fonction retourne false si le client n'est pas connecté
 * @return true 
 * @return false 
 */
bool interface_WIFI_Check_Connexion()
{
    if(client.available())
    {
        return true;
    }
    else
    {
        return false;
    }
}


unsigned char interface_WIFI_Read()
{
    return client.read();
}




/**
 * @brief Fermeture du serveur
 * 
 */
void interface_WIFI_eteint(void)
{
    client.stop();
}
