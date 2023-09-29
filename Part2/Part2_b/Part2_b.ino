#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "OPPO A77s"; // replace with your WiFi network name
const char* password = "123456789"; // replace with your WiFi network password
const char* server = "192.168.42.168"; // replace with your MQTT broker's IP address
const int port = 54322;

WiFiClient client;
WiFiUDP udp;

// PubSubClient client(espClient);

void setup() {
  Serial.begin(9600); // initialize the serial communication
  delay(1000); // wait for the serial port to be ready
  
  pinMode(LED_BUILTIN, OUTPUT);

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
    // char buffer[packetSize];
    // udp.read(buffer, packetSize);
    // buffer[packetSize] = '\0'; // null terminate the char array
    // char *value = strtok(buffer, ","); // split the buffer using comma as delimiter
    // float f1 = atof(value); // convert the first float value
    // value = strtok(NULL, ","); // get next value after comma
    // float f2 = atof(value); // convert the second float value
    float f1, f2;
    char buffer[8];
    int length = udp.read(buffer, 8);
    if (length == 8) {
      memcpy(&f1, &buffer[0], 4);
      memcpy(&f2, &buffer[4], 4);
    }

    
    if (f2<=20 && f1<=20){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN,LOW);
      delay(100);    
    }

    else if (f2 <= 20){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(300);
      digitalWrite(LED_BUILTIN,LOW);
      delay(300);  
    }

    Serial.print("Fuel 1: ");
    Serial.print(f1);
    Serial.print(", ");
    Serial.print("Fuel 2: ");
    Serial.println(f2);
    
  }


// int packetSize = udp.parsePacket();
  // if (packetSize) {
    // Serial.println("Received packet from RPi:");
    // char packetBuffer[packetSize];
    // udp.read(packetBuffer, packetSize);
    // float receivedValue = atof(packetBuffer);
    
  //   if (receivedValue <= 20){
  //     digitalWrite(LED_BUILTIN,HIGH);
  //     delay(250);
  //     digitalWrite(LED_BUILTIN,LOW);
  //     delay(250);  
  //   }

  //   else{
  //     digitalWrite(LED_BUILTIN,LOW);
  //   }
  //   Serial.print("Value received: ");
  //   Serial.println(receivedValue);
  // }

}
