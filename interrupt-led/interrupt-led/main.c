/*
 * interrupt-led.c
 *
 * Created: 24/01/2026 10:43:11
 * Author : Vinicius Duarte
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect); //Interrupção para acionamento do led 

int main(void)
{
	//GPIO 
	DDRD &= ~(1 << 2);	    //PD3 como entrada 
	DDRC |= (1 << 2);       //PC2 como saída 
	PORTD |= (1 << 2);       //pull-up habilitado em PD2      

	//Configurando a Interrupção
	EICRA = 0b10;     //define a interrupção externa INT0 para borda de descida 
	EIMSK = 0b1;      //habilita INT0 
	
	/* Outra forma: 
	EICRA = (1 << ISC01);
    EIMSK = (1 << INT0);
	 */
	
	sei();				//habiltia todas as interrupções, setando o bit 1 do registrador SREG 

    while (1) 
    {	
    }
}


//Interrupção para acionamento do led
ISR(INT0_vect){
	PORTC ^=  ( 1 << 2 );
}
