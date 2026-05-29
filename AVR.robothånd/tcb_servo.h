#ifndef TCB_SERVO_H
#define TCB_SERVO_H

#include <stdint.h>

void TCB_servo_init(void);

void servo6_set_us(uint16_t us);
void servo5_set_us(uint16_t us);
void servo4_set_us(uint16_t us); 

#endif