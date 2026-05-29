#include <avr/io.h>
#include "usart.h"

#define F_CPU 4000000UL

void USART0_init(void)
{

	PORTA.DIRSET = PIN0_bm;

	
	PORTA.DIRCLR = PIN1_bm;

	
	PORTMUX.USARTROUTEA = PORTMUX_USART0_DEFAULT_gc;


	USART0.BAUD = 138;

	USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}

uint8_t USART0_available(void)
{
	return (USART0.STATUS & USART_RXCIF_bm);
}

uint8_t USART0_read(void)
{
	while (!USART0_available());
	return USART0.RXDATAL;
}