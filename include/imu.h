#pragma once

void imu_init();
void imu_read(float &ax, float &ay, float &az,
              float &gx, float &gy, float &gz);
              