#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>

#include <ESPAsyncWebServer.h>          // Add this for Web Server library https://me-no-dev.github.io/ESPAsyncWebServer/





#define HTTP_PORT 80

AsyncWebServer server(HTTP_PORT);

void setup() {
    initWebServer();
}


// Replace STATE directive by CSS class which corresponds to current state of sensor "<div id="sensor" class="%STATE%"></div>"

String processor(const String &var) {
    return String(var == "STATE" && sensor.on ? "on" : "off");
}       

//Add something like this to Web UI Design html
//<body>
// <div class="panel">
//  <h1>ESP32 remote</h1>
//  <div id="sensor" class="%STATE%"></div>
// </div>
//</body>

void onRootRequest(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/MAL_Website.html", "text/html", false, processor);
}

void initWebServer() {
    server.on("/", onRootRequest);
    server.serveStatic("/", SPIFFS, "/").setDefaultFile ("MAL_Website.html);            // specify what should be the default SPIFFS file to send to the browser if the URL only designates the HTTP root path - do we use SPIFFS? - host resources/ interface files in flash memory of ESP32 on SPIFF file system
    
    server.begin();
}


