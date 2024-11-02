#include "settings.h"

#include <ArduinoJson.h>
#include <SPIFFS.h>


const String defaultAlarm = "08:00";

void saveSettings(String newTime) {
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Create a JSON document
    StaticJsonDocument<200> doc;
    doc["alarmTime"] = newTime;

    // Open the file for writing
    File file = SPIFFS.open("/config.json", "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    // Serialize JSON to file
    serializeJson(doc, file);
    file.close();
}

String loadSettings(bool retry) {
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount file system");
        return defaultAlarm;
    }

    // Open the file for reading
    File file = SPIFFS.open("/config.json", "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        if (retry) {
            saveSettings(defaultAlarm);
            return loadSettings(false);
        }
        else {
            return defaultAlarm;
        }
    }

    // Deserialize JSON from file
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("Failed to read file, using default configuration");
        Serial.println(error.code());
        return defaultAlarm;
    }

    // Get the saved alarm time
    String savedTime = doc["alarmTime"].as<String>();
    Serial.print("Loaded Alarm Time: ");
    Serial.println(savedTime);

    file.close();
    return savedTime;
}