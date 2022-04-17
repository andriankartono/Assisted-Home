#include <WiFi.h>
#include <HTTPClient.h>
#include <M5Stack.h>
 
const char* ssid = "AndroidAP60b8";
const char* password =  "crocodille";
 
void setup() {
 
  M5.begin();
  M5.Power.begin();
  delay(4000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    M5.Lcd.print("Connecting to WiFi..");
  }
 
  M5.Lcd.print("Connected to the WiFi network");
 
}

void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin("https://ptsv2.com/t/zoham-1638801122/post");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
  
   int httpResponseCode = http.POST("POSTING from ESP32");   //Send the actual POST request
  
   if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
  
    M5.Lcd.print(httpResponseCode);   //Print return code
    M5.Lcd.print(response);           //Print request answer
  
   }else{
  
    M5.Lcd.print("Error on sending POST: ");
    M5.Lcd.print(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    M5.Lcd.print("Error in WiFi connection");   
  
 }
  
  delay(10000);  //Send a request every 10 seconds
  
}
