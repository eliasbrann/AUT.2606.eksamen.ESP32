#include <avr/io.h>
#include "tca_servo.h"


void TCA_servo_init(void)
{

	PORTB.DIRSET = PIN0_bm | PIN1_bm;

	
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTB_gc;


	TCA0.SINGLE.CTRLA = 0;


	TCA0.SINGLE.CTRLB =
	TCA_SINGLE_WGMODE_SINGLESLOPE_gc |
	TCA_SINGLE_CMP0EN_bm |
	TCA_SINGLE_CMP1EN_bm;


	TCA0.SINGLE.PER = 5000;


	TCA0.SINGLE.CMP0 = 375; 
	TCA0.SINGLE.CMP1 = 375; 

	TCA0.SINGLE.CTRLA =
	TCA_SINGLE_CLKSEL_DIV16_gc |
	TCA_SINGLE_ENABLE_bm;
}


void servo7_set_us(uint16_t us)
{
	if (us < 500) us = 500;
	if (us > 2500) us = 2500;

	TCA0.SINGLE.CMP0 = us / 4;
}


void servo8_set_us(uint16_t us)
{
	if (us < 500) us = 500;
	if (us > 2500) us = 2500;

	TCA0.SINGLE.CMP1 = us / 4;
}