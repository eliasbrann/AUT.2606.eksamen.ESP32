#include <avr/io.h>
#define F_CPU 4000000UL
#include <stdlib.h>
#include <string.h>

#include "usart.h"
#include "tca_servo.h"
#include "tcb_servo.h"

#define BUFFER_SIZE 64

#define INPUT_MIN 2400
#define INPUT_MAX 4000

#define SERVO_MIN 600
#define SERVO_MAX 2400

char buffer[BUFFER_SIZE];
uint8_t index = 0;

uint16_t map_to_servo(uint16_t val)
{
	if (val < INPUT_MIN) val = INPUT_MIN;
	if (val > INPUT_MAX) val = INPUT_MAX;

	return SERVO_MIN + ((uint32_t)(val - INPUT_MIN) * (SERVO_MAX - SERVO_MIN)) /
	(INPUT_MAX - INPUT_MIN);
}

int main(void)
{
	USART0_init();

	TCA_servo_init(); 
	TCB_servo_init();  

	while (1)
	{
		if (USART0_available())
		{
			char c = USART0.RXDATAL;

			if (c != '\n' && c != '\r' && index < BUFFER_SIZE - 1)
			{
				buffer[index++] = c;
			}
			else if (c == '\n')
			{
				buffer[index] = '\0';
				index = 0;

				char *token = strtok(buffer, ",");

				for (uint8_t i = 0; i < 5 && token != NULL; i++)
				{
					while (*token == '[' || *token == ' ')
					{
						token++;
					}

					uint16_t val = atoi(token);
					uint16_t servo = map_to_servo(val);

					if (i == 0)
					{
						servo8_set_us(servo);
					}
					else if (i == 1)
					{
						servo7_set_us(servo); 
					}
					else if (i == 2)
					{
						servo6_set_us(servo); 
					}
					else if (i == 3)
					{
						servo5_set_us(servo); 
					}
					else if (i == 4)
					{
						servo4_set_us(servo); 
					}

					token = strtok(NULL, ",");
				}
			}
		}
	}
}