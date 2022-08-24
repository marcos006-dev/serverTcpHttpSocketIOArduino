#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x6C, 0xFE };
IPAddress ip(192,168,0,225);
IPAddress server(192,168,0,101);

int ventilador = 8;
int pinVal = 0;
int port = 1337;
EthernetClient client;

void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Conectando...");
  if (client.connect(server, port)) {
    Serial.println("Conectado.");
  } else {
    Serial.println("Error: Conexion fallida.");
  }
  pinMode(ventilador, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    if (c == '1') {
      pinVal = HIGH;
      client.print("Led Prendido");
      digitalWrite(LED_BUILTIN, pinVal);
       delay(1000);  
    } else if (c == '0') {
      pinVal = LOW;
      client.print("Led apagado");
      digitalWrite(LED_BUILTIN, pinVal);
       delay(1000);  
    }
    digitalWrite(ventilador, pinVal);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("desconectado.");
    client.stop();
    delay(1000);
    client.connect(server, port);
  } 

}
