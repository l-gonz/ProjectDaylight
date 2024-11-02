
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "settings.h"

const char* ssid = "MiCasa";
const char* password = "Rhythm4Tist";


AsyncWebServer server(80);
String alarmTime;


void setupWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());
}

void setupServer() {
    setupWiFi();
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        alarmTime = loadSettings(true);
        request->send(200, "text/html", "<html><body>"
                                        "<h1>Set Alarm Time</h1>"
                                        "<p>Current alarm time: " + alarmTime + "</p>"
                                        "<form action='/set' method='post'>"
                                        "<label for='alarm'>Alarm Time (HH:MM): </label>"
                                        "<input type='text' name='alarm'><br><br>"
                                        "<input type='submit' value='Set Alarm'>"
                                        "</form></body></html>");
    });

    server.on("/set", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("alarm", true)) {
            String alarmTime = request->getParam("alarm", true)->value();
            Serial.print("Alarm Time Set to: ");
            Serial.println(alarmTime);
            request->redirect("/");
            saveSettings(alarmTime);
        } else {
                request->send(400, "text/plain", "Invalid request");
        }
    });
    server.begin();
}