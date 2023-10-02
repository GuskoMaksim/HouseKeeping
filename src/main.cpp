#include <Arduino.h>

constexpr uint32_t refresh_interval_ms = 1000;
uint32_t timer_to_update_ms;

void setup() {
    Serial.begin(9600);
    Serial.println("Start");
};

void loop() {
    if (millis() - timer_to_update_ms > refresh_interval_ms) {
        timer_to_update_ms = millis();
    }
};
