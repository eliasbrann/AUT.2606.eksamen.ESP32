#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include "imu.h"

Adafruit_LSM6DSOX lsm6;

void imu_init() {
    Wire.begin();

    if (!lsm6.begin_I2C()) {
        Serial.println("LSM6DSO not found!");
        while (1);
    }

    lsm6.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
    lsm6.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
}

void imu_read(float &ax, float &ay, float &az,
              float &gx, float &gy, float &gz) {

    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    lsm6.getEvent(&accel, &gyro, &temp);

    ax = accel.acceleration.x;
    ay = accel.acceleration.y;
    az = accel.acceleration.z;

    gx = gyro.gyro.x;
    gy = gyro.gyro.y;
    gz = gyro.gyro.z;
}