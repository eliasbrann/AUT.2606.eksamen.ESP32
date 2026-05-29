#ifndef TCA_SERVO_H
#define TCA_SERVO_H

#include <stdint.h>

void TCA_servo_init(void);

void servo7_set_us(uint16_t us); 
void servo8_set_us(uint16_t us); 

#endif