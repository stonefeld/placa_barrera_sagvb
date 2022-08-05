#include <WiFi.h>
#include <WiFiManager.h>

namespace Utils {

  String connectWiFi(const char *ssid, const char *password) {
#ifdef WiFiManager_h
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    bool res = wm.autoConnect("ESPBarreraEntrada-AP", "wifiwifi");
    if (res) {
      IPAddress ipAddr = WiFi.localIP();
      Serial.print("\nConnected. My IP address is: ");
      Serial.print(ipAddr.toString());
      Serial.print(". My hostname is: ");
      Serial.println(WiFi.getHostname());
      return ipAddr.toString();
    } else {
      Serial.print(" Failed!!!");
      return String("Error");
    }
#else
    // Me aseguro que el dispositivo no este conectado.
    WiFi.disconnect();

    // Configuro el modulo WiFi.
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);

    // Mientras no este conectado imprimo un mensaje de aviso y le dejo tiempo para que establezca la conexion.
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
      if ((++i % 16) == 0)
        Serial.print(" still trying to connect ");

      if ((++i % 256) == 0)
        break;
    }

    // En este punto se supone que la conexion a la red WiFi esta completa e imprimo la IP y el hostname del mismo.
    if (WiFi.status() == WL_CONNECTED) {
      IPAddress ipAddr = WiFi.localIP();
      Serial.print("\nConnected. My IP address is: ");
      Serial.print(ipAddr.toString());
      Serial.print(". My hostname is: ");
      Serial.println(WiFi.getHostname());
      return ipAddr.toString();
    } else {
      Serial.print(" Failed!!!");
      return String("Error");
    }
#endif
  }

  String reconnectWiFi() {
    // Trato de reconectar al ultimo wifi que se conecto.
    WiFi.reconnect();

    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
      if ((++i % 16) == 0)
        Serial.print(" still trying to connect ");

      if ((++i % 256) == 0)
        break;
    }

    // En este punto se supone que la conexion a la red WiFi esta completa e imprimo la IP y el hostname del mismo.
    if (WiFi.status() == WL_CONNECTED) {
      IPAddress ipAddr = WiFi.localIP();
      Serial.print("\nConnected. My IP address is: ");
      Serial.print(ipAddr.toString());
      Serial.print(". My hostname is: ");
      Serial.println(WiFi.getHostname());
      return ipAddr.toString();
    } else {
      Serial.print(" Failed!!!");
      return String("Error");
    }
  }

  bool getWiFiStatus() {
    return(WiFi.status() == WL_CONNECTED);
  }

}
