#include <WiFi.h>
const char* ssid = "thalassophiles";
const char* password = "82103462529594073993";


const uint16_t port = 10004;
const char * host = "192.168.178.33";
WiFiClient client;
byte server_response=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("");
  Serial.println("WiFi connected");
}

  while (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(500);
}
  Serial.println("Client Connected");
}



void loop() {
  // put your main code here, to run repeatedly:


    client.print("HELLO 1");
    delay(30000);
    client.print("HELLO 0");
    delay(30000);
    
    server_response = client.read();
 
    while(server_response==-1){
      delay(500);
      server_response = client.read();
      Serial.println("waiting for response");
  }
}
