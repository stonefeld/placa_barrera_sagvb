#include <WiFi.h>

#include "Utils.h"
#include "WiFiConfig.h"

#define SOC_PORT 5050
#define SOC_AP 'A'
#define SOC_CER 'C'
#define SOC_TEM 'T'

WiFiServer socket(SOC_PORT);

void setup() {
  Serial.begin(115200);

  String ipAddr = Utils::connectWiFi(ssid, password);
  delay(1000);
  socket.begin();

  pinMode(11, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(25, INPUT);
}

void loop() {
  int aux = 0, salida = 0, numero = 0;
  uint8_t data[30];

  WiFiClient client = socket.available();
  if (client) {
    Serial.println("Client disponible");
    while (client.connected()) {
      client.read(data, 30);
      Serial.print("El cliente envio: ");
      Serial.println((char*)data);

      switch (data[1]) {
        case SOC_TEM: {
          digitalWrite(16, HIGH);
          delay(500);
          salida = 0;
          aux = 0;
          numero = 0;

          while (salida == 0 && numero < 500) {
            delay(50);
            numero++;

            if (digitalRead(25) == 1)
              aux = 1;

            if (digitalRead(25) == 0 && aux == 1) {
              aux = 0;
              salida = 1;
            }
          }
          digitalWrite(16, LOW);
        } break;

        case SOC_AP: {
          digitalWrite(16, HIGH);
          delay(500);
        } break;

        case SOC_CER: {
          digitalWrite(16, LOW);
          delay(500);
        } break;
      }
    }
  }
}
