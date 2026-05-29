#include <Arduino.h>
#include "LED_test.h"
#include "adc_read.h"
#include "bluetooth.h"
#include "imu.h"

const int num_pins = 5;
int values[num_pins];

void setup() {
    Serial.begin(115200);

    adc_init();
    led_init();
    bt_init();
    imu_init();

    delay(2000);
}

void loop() {
    adc_read(values, num_pins);

    // Leser IMU
    float ax, ay, az, gx, gy, gz;
    imu_read(ax, ay, az, gx, gy, gz);

    // Print ADC
    for (int i = 0; i < num_pins; i++) {
        Serial.print(values[i]);
        Serial.print(",");
    }

    // Print IMU 
    Serial.print(ax); Serial.print(",");
    Serial.print(ay); Serial.print(",");
    Serial.print(az); Serial.print(",");
    Serial.print(gx); Serial.print(",");
    Serial.print(gy); Serial.print(",");
    Serial.println(gz);

    // Sender bare ADC med Bluetooth 
    if (bt_connected()) {
        bt_send(values, num_pins);
     
    }
//LED blinker så kjører koden
    led_update();

    delay(10);  
}