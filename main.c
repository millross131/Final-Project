/*
 * Lumin.c
 *
 * Created: 4/1/2022 7:53:35 PM
 * Author : millross
 */ 

#define F_CPU 16000000
#define SENSORVALUE 2
#define BAUD 9600
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "usart.h"

void InitADC();
uint16_t ReadADC(uint8_t ADCchannel);

void InitADC()
{
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}


uint16_t ReadADC(uint8_t ADCchannel)
{
	ADMUX = (ADMUX & 0xF0)
	ADMUX |= (ADCchannel & 0x0F);
	ADCSRA |= (1<<ADSC);
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}

int main(void)
{
	double value1, value2;
	USART_init(BAUD);
	USART_putstr("#USART init\n");
	InitADC();
	USART_putstr("#ADC init\n");
	DDRC = 0b00000010;
	PORTC = 0b00000000;

	while(1)
	{
		value1=ReadADC(0);
		_delay_ms(1);
		value2=ReadADC(0);
		char str[10];
		itoa(value1,str,10);
		USART_putstr(str);
		USART_putstr("\n");
		if(value1-value2 > SENSORVALUE || value2-value1 > SENSORVALUE)
		{
			PORTC ^= 0b00000010; 
			_delay_ms(100);
		}
	}
}
