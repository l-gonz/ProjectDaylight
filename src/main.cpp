#include <Arduino.h>
// #include <FastLED.h>
// #include <NTPClient.h>
// #include <WiFiUdp.h>

#include "settings.h"
#include "server.h"

#define LED_PIN     19     // Data pin connected to LED strip
#define NUM_LEDS    60     // Number of LEDs in your strip
#define MAX_BRIGHTNESS 255 // Maximum brightness level


// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000); // Adjust timezone offset as needed
bool alarmTriggered;

// CRGB leds[NUM_LEDS];
unsigned long previousMillis = 0; // Stores the last time we updated
const unsigned long interval = 1000; // Update every 1 second
int brightnessStep = MAX_BRIGHTNESS / 900; // Step size for brightness
int currentBrightness = 0; // Start at 0 brightness


// String getFormattedTime();
// void gradualBrightening();


void setup() {
    Serial.begin(115200);

    setupServer();

    // timeClient.begin();
    // timeClient.update();

    // FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    // FastLED.setBrightness(0);
}

void loop() {
    // timeClient.update();
    // String currentTime = getFormattedTime();

    // // Check if it's time to start the brightening sequence
    // if (currentTime == alarmTime && !alarmTriggered) {
    //     Serial.println("Alarm triggered! Starting brightening sequence.");
    //     alarmTriggered = true; // Only trigger once
    // }

    // // If alarm is triggered, run the gradual brightening sequence
    // if (alarmTriggered) {
    //     gradualBrightening();
    // }

    //TODO Add alarm reset functionality
    //TODO Add day of the week checks
}


// Function to get current time as a formatted string
// String getFormattedTime() {
//     int hours = timeClient.getHours();
//     int minutes = timeClient.getMinutes();
//     char timeStr[6];
//     sprintf(timeStr, "%02d:%02d", hours, minutes);
//     return String(timeStr);
// }

// Gradual brightening sequence
// void gradualBrightening() {
//     unsigned long currentMillis = millis();

//     // Check if it's time to update brightness
//     if (currentMillis - previousMillis >= interval && currentBrightness < MAX_BRIGHTNESS) {
//         previousMillis = currentMillis;  // Save the last time we updated

//         // Increase brightness
//         currentBrightness += brightnessStep;
//         if (currentBrightness > MAX_BRIGHTNESS) currentBrightness = MAX_BRIGHTNESS;

//         // Set brightness and update LEDs
//         FastLED.setBrightness(currentBrightness);
//         fill_solid(leds, NUM_LEDS, CRGB::White);
//         FastLED.show();
//     }
// }
