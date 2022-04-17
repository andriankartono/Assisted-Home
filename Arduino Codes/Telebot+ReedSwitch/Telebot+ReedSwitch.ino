#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Set GPIOs for LED and reedswitch
const int reedSwitch = 4;
const int led = 2; //optional

// Detects whenever the door changed state
bool changeState = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

// Auxiliary variables (it will only detect changes that are 1500 milliseconds apart)
unsigned long previousMillis = 0; 
const long interval = 5000;

const char* ssid = "AndroidAP60b8";
const char* password = "crocodille";

// Initialize Telegram BOT
#define BOTtoken "5030750740:AAG3s0o5BBcTD1fdTJUAW0bihEXuGN2CyPE"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "701111952"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup(){
  Serial.begin(115200);

  pinMode(reedSwitch, INPUT_PULLUP);
  //state = digitalRead(reedSwitch);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  

  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop(){
  state=digitalRead(reedSwitch);
  if(state==LOW){
    Serial.println("Door Opened");
    bot.sendMessage(CHAT_ID, "The door is opened. Please close the door. Next Reminder in" + String(interval/1000) + "seconds", "");
    delay(interval);
  }else if(state==HIGH){
    Serial.println("Door Closed");
    delay(interval);
  }
}
