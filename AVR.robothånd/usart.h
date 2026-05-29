#ifndef USART_H
#define USART_H

#include <stdint.h>

void USART0_init(void);
uint8_t USART0_available(void);
uint8_t USART0_read(void);

#endif