/*
 * blink.c
 *
 * Created: 20/01/2026 21:51:01
 * Author : Vinicius Duarte
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/* Replace with your application code */
	DDRB |= (1 << 5);   // PB5 como saída
	
	while (1)
	{
		PORTB = 0b00100000; //Pino PB5 em nível alto
		_delay_ms(1000);
		PORTB = 0b00000000; //Pino PB5 em nível baixo
		_delay_ms(1000);
	}
}