#include <Arduino.h>
#include "adc_read.h"

//ADC1 - fungerer med bluetooth
const int adc_pins[] = {33, 32, 35, 34, 36};
const int num_pins = sizeof(adc_pins) / sizeof(adc_pins[0]);


void adc_read(int values[], int length) {
    for (int i = 0; i < length; i++) {
        values[i] = analogRead(adc_pins[i]);
    }
}
