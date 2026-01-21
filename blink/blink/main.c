/*
 * blink.c
 *
 * Created: 20/01/2026 21:51:01
 * Author : Vinicius Duarte
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = 0b00100000; //Habilita o pino PB5 como saída 

    while (1) 
    {
		PORTB = 0b00100000;
		PORTB = 0b00000000;

		
    }
}

