#include "Arduino.h"
#include "LED_test.h"
#define LED_PIN 25

void led_init() {
    pinMode(LED_PIN, OUTPUT);
}

void led_update() {
    static unsigned long last = 0;
    static bool state = false;

    if (millis() - last > 500) {
        last = millis();
        state = !state;
        digitalWrite(LED_PIN, state);
    }
}
