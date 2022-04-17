#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// Set GPIOs for reedswitch
const int reedSwitch = 4;

// Detects whenever the door changed state
bool changeState = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

// Auxiliary variables (it will only detect changes that are 1500 milliseconds apart)
unsigned long previousMillis = 0; 
const long interval = 6000000;

//Parameters for WIFI Connection
const char* ssid = "...";
const char* password = "...";

//Parameters for TCP connection
const uint16_t port = 80;
const char * host = "192.168.1.101";
//WiFiClientSecure client;
WiFiClient client;




/*ICACHE_RAM_ATTR void changeDoorStatus() {
  //Can be changed if wanted
  client.print("State Changed" + digitalRead(reedSwitch));
}*/

byte server_response=0;
int first_try;

void setup(){
  Serial.begin(115200);

  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);

  //attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  

  //connect to server.py
  while (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(500);
  }
  Serial.println("Client Connected");
}

void loop(){
  //Serial.println("New Loop started");
  //Check if a minute has passed. Yes-> send door status via tcp.
  state=digitalRead(reedSwitch);
  if(state==LOW){
   client.print("Door 1");
   Serial.println(server_response);
   Serial.println(client.connected());
   Serial.print("Door 1. Time: ");
  }else if(state==HIGH){
    client.print("Door 0");
    Serial.println(client.connected());
    Serial.println(server_response);
    Serial.print("Door 0. Time: ");
  }
  Serial.println(millis()/1000);
  delay(5000);
  
  server_response = client.read();
  while(server_response==-1){
    delay(500);
    server_response = client.read();
    Serial.println("waiting for response");
  }
}
