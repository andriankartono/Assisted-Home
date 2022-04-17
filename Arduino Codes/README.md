Voraussetzung:
Die bibliothek für ESP32 herunterladen.
(Add this link to file->preferences https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
and then go to tools->boardmanager)

Implementierung:
1. Zeilen zu ändern:
SSID: <deine WiFI Name>
Password: <deine WiFI Password>
http.begin(<Website API>)
(Get your website API for testing: http://ptsv2.com/)

2. Wenn du kein M5 stack verwenden:
find and replace: M5.Lcd.print -> Serial.println

3. For Telebot Code:
Edit your user id to your own telegram Id
(Get ID with ID Bot)
