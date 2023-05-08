
#include "main.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include "interface_WIFI.h"


#define UDP_PORT 4210

// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";

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

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);


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
    
    return 1;
}

/**
 * @brief La fonction retourne le nombre de data à lire
 * 
 * @return true 
 * @return false 
 */
int interface_WIFI_Data_Available()
{
    return UDP.parsePacket();
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
    return true;
    // if(client.connected())
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
}


int interface_WIFI_Read(unsigned char * packet, int length)
{
    int len = UDP.read(packet, length);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");

    for(int i = 0; i < len; i++)
    {
        Serial.print((char)packet[i]);
    }
    Serial.println("");

    return len;
}


int interface_WIFI_Send(unsigned char * packet, int length)
{
        // Send return packet
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write(packet, length);
    UDP.endPacket();

    return 0;
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
