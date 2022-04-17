#include <ArduinoJson.h> //--> JSON Format

AsyncWebSocket ws("/ws"); // --> Websocket definieren

// ----------------------------------------------------------------------------
// WebSocket initialization //--> ws startup
// ----------------------------------------------------------------------------
void notifyClients() {    // --> WebSocket Data Exchange
    // ws.textAll(sensor.on ? "on" : "off"); //--> textAll is in AsyncWebSocket class, is that enough or do we have to use JSON
    
    const uint8_t size = JSON_OBJECT_SIZE(1); //--> JSON Object to notify the clients
    StaticJsonDocument<size> json;
    json["status"] = sensor.on ? "on" : "off";

    char buffer[17];
    size_t len = serializeJson(json, buffer);
    ws.textAll(buffer, len);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) { // --> WebSocket Data Exchange
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        
        // data[len] = 0; //--> if textAll is used

        const uint8_t size = JSON_OBJECT_SIZE(1); //--> JSON handle Message
        StaticJsonDocument<size> json;
        DeserializationError err = deserializeJson(json, data);
        if (err) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }
        const char *action = json["action"];

        if (strcmp((char*)data, "toggle") == 0) {
            sensor.on = !sensor.on;
            notifyClients();
        }
    }
}

void onEvent(AsyncWebSocket       *server,
             AsyncWebSocketClient *client,
             AwsEventType          type,
             void                 *arg,
             uint8_t              *data,
             size_t                len) {

    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
client->remoteIP().toString().c_str()); //--> JSON 
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
handleWebSocketMessage(arg, data, len); //--> JSON
break
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void initWebSocket() {
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}


// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

void setup() {
    initWebSocket(); // --> Websocket initialisieren
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------

void loop() {
    ws.cleanupClients(); //--> necessary for Websocket? limits number of clients

    if (sensor.on) {
        notifyClients();  // --> Websocket Data Exchange
    }
}
