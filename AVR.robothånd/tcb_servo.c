#include <avr/io.h>
#include <avr/interrupt.h>
#include "tcb_servo.h"

#define FRAME_US 20000UL
#define TICKS_PER_US 2UL

#define SERVO_MIN_US 600
#define SERVO_MAX_US 2400

static volatile uint16_t servo6_us = 1500;
static volatile uint16_t servo5_us = 1500;
static volatile uint16_t servo4_us = 1500;

static volatile uint8_t servo6_state = 0;
static volatile uint8_t servo5_state = 0;
static volatile uint8_t servo4_state = 0;

static uint16_t us_to_ticks(uint16_t us)
{
	return (uint16_t)((uint32_t)us * TICKS_PER_US);
}

void TCB_servo_init(void)
{
	
	PORTA.DIRSET = PIN5_bm | PIN4_bm | PIN3_bm;
	PORTA.OUTCLR = PIN5_bm | PIN4_bm | PIN3_bm;


	TCB0.CTRLA = 0;
	TCB0.CTRLB = TCB_CNTMODE_INT_gc;
	TCB0.CNT = 0;
	TCB0.CCMP = us_to_ticks(1500);
	TCB0.INTFLAGS = TCB_CAPT_bm;
	TCB0.INTCTRL = TCB_CAPT_bm;
	TCB0.CTRLA = TCB_CLKSEL_DIV2_gc | TCB_ENABLE_bm;

	
	TCB1.CTRLA = 0;
	TCB1.CTRLB = TCB_CNTMODE_INT_gc;
	TCB1.CNT = 0;
	TCB1.CCMP = us_to_ticks(1500);
	TCB1.INTFLAGS = TCB_CAPT_bm;
	TCB1.INTCTRL = TCB_CAPT_bm;
	TCB1.CTRLA = TCB_CLKSEL_DIV2_gc | TCB_ENABLE_bm;


	TCB2.CTRLA = 0;
	TCB2.CTRLB = TCB_CNTMODE_INT_gc;
	TCB2.CNT = 0;
	TCB2.CCMP = us_to_ticks(1500);
	TCB2.INTFLAGS = TCB_CAPT_bm;
	TCB2.INTCTRL = TCB_CAPT_bm;
	TCB2.CTRLA = TCB_CLKSEL_DIV2_gc | TCB_ENABLE_bm;

	sei();
}

void servo6_set_us(uint16_t us)
{
	if (us < SERVO_MIN_US) us = SERVO_MIN_US;
	if (us > SERVO_MAX_US) us = SERVO_MAX_US;

	servo6_us = us;
}

void servo5_set_us(uint16_t us)
{
	if (us < SERVO_MIN_US) us = SERVO_MIN_US;
	if (us > SERVO_MAX_US) us = SERVO_MAX_US;

	servo5_us = us;
}

void servo4_set_us(uint16_t us)
{
	if (us < SERVO_MIN_US) us = SERVO_MIN_US;
	if (us > SERVO_MAX_US) us = SERVO_MAX_US;

	servo4_us = us;
}

ISR(TCB0_INT_vect)
{
	TCB0.INTFLAGS = TCB_CAPT_bm;
	TCB0.CNT = 0;

	if (servo6_state == 0)
	{
		PORTA.OUTSET = PIN5_bm;
		TCB0.CCMP = us_to_ticks(servo6_us);
		servo6_state = 1;
	}
	else
	{
		PORTA.OUTCLR = PIN5_bm;
		TCB0.CCMP = us_to_ticks(FRAME_US - servo6_us);
		servo6_state = 0;
	}
}

ISR(TCB1_INT_vect)
{
	TCB1.INTFLAGS = TCB_CAPT_bm;
	TCB1.CNT = 0;

	if (servo5_state == 0)
	{
		PORTA.OUTSET = PIN4_bm;
		TCB1.CCMP = us_to_ticks(servo5_us);
		servo5_state = 1;
	}
	else
	{
		PORTA.OUTCLR = PIN4_bm;
		TCB1.CCMP = us_to_ticks(FRAME_US - servo5_us);
		servo5_state = 0;
	}
}

ISR(TCB2_INT_vect)
{
	TCB2.INTFLAGS = TCB_CAPT_bm;
	TCB2.CNT = 0;

	if (servo4_state == 0)
	{
		PORTA.OUTSET = PIN3_bm;
		TCB2.CCMP = us_to_ticks(servo4_us);
		servo4_state = 1;
	}
	else
	{
		PORTA.OUTCLR = PIN3_bm;
		TCB2.CCMP = us_to_ticks(FRAME_US - servo4_us);
		servo4_state = 0;
	}
}