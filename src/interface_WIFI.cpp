
#include "main.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include "interface_WIFI.h"

WiFiServer server(80);
WiFiClient client;
IPAddress myIP;


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


  myIP = WiFi.softAPIP();

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
    //Serial.print("AP IP address: ");
    //Serial.println(myIP);
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
    if(client.connected())
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
    int index = 0;
    unsigned char val = 0;
    while(client.available())
    {
        char c = client.read();

        if(index == 0 && c == 'G')
        {
            index++;
        }
        else if(index == 1 && c == 'E')
        {
            index++;
        }
        else if(index == 2 && c == 'T')
        {
            index++;
        }
        else if(index == 3 && c == ' ')
        {
            index++;
        }
        else if(index == 4 && c == '/')
        {
            index++;
        }
        else if(index == 5 && c == '1')
        {
            val = '1';
        }
        else if(index == 5 && c == '0')
        {
            val = '0';
        }
        else
        {
            index = 0;
        }
        Serial.print(c);
    }

    return val;
}


void interface_WIFI_Show_Page()
{
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"1\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"0\">here</a> to turn OFF the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
}

/**
 * @brief Fermeture du serveur
 * 
 */
void interface_WIFI_eteint(void)
{
    client.stop();
}
