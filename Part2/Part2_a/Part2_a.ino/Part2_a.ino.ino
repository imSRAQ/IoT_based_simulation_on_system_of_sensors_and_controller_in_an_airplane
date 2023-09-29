#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "OPPO A77s"; // replace with your WiFi network name
const char* password = "123456789"; // replace with your WiFi network password
const char* server = "192.168.42.168"; // replace with your MQTT broker's IP address
const int port = 54321;

WiFiClient client;
WiFiUDP udp;
char packetBuffer[255];

// PubSubClient client(espClient);

void setup() {
  Serial.begin(9600); // initialize the serial communication
  delay(1000); // wait for the serial port to be ready
  Serial.println("Connecting to WiFi...");
  
  WiFi.mode(WIFI_STA);
  // String connection_string = "Connecting to wifi network.";
  Serial.print("Connecting to wifi network : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
     delay(500);
     Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected: Node IP : ");
  Serial.println(WiFi.localIP());

  udp.begin(port);
}

void loop() {

  int packetSize = udp.parsePacket();
  if (packetSize) {
      int length = udp.read(packetBuffer, 255); //Check for incoming packets
      packetBuffer[packetSize] = '\0';  // null-terminate the string
      Serial.print("Received data: ");
      Serial.println(packetBuffer);
  }

  String start = String(packetBuffer);
  Serial.print(start);
  if(start == "S"){
    float f1 = 100 , f2 = 100;
    int t = 0;

    while(f1 > 0){
      f1 = (-0.23 * t) + 100;
      f2 = (-0.29 * t) + 100;
      t += 2;
      
      if(f1<0){
        f1 = 0;
      }
      else if (f2<0 || f1<0){
        f2 = 0;
      }

      Serial.print("Fuel 1: ");
      Serial.print(f1);
      Serial.print(", ");
      Serial.print("Fuel 2: ");
      Serial.println(f2);
      Serial.println("");
      
      sprintf(packetBuffer, "%f,%f", f1, f2);  // the format specifier "%f,%f" specifies that two float values f1 and f2 will be formatted and separated by a comma ,. The resulting formatted string will be stored in packetBuffer 
    
      udp.beginPacket(server, port);
      // String fuel1 = String(f1);
      // udp.write(fuel1.c_str(), fuel1.length());
      // String fuel2 = String(f2);
      // udp.write(fuel2.c_str(), fuel2.length());
      udp.write(packetBuffer);
      udp.endPacket();

      delay(500);

      int packetSize = udp.parsePacket();
      if (packetSize) {
        int length = udp.read(packetBuffer, 255); //Check for incoming packets
        packetBuffer[packetSize] = '\0';  // null-terminate the string
        Serial.print("Received data: ");
        Serial.println(packetBuffer);

      }
      
      String ack = String(packetBuffer);
        // Serial.println(ack);

      while(ack != "RS"){
        // Serial.println(ack);
        delay(100);
      }
    }}

}

