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
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}


uint16_t ReadADC(uint8_t ADCchannel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}

int main(void)
{
	double value1, value2;
	// Initialise the USART
	USART_init(BAUD);
	USART_putstr("#USART init\n");
	// Initialise the ADC
	InitADC();
	USART_putstr("#ADC init\n");

	// PC1 pin of PORTC output, the rest input.
	DDRC = 0b00000010;
	// set initial values to PORTC low.
	PORTC = 0b00000000;

	while(1)
	{
		// read value and store in val1
		value1=ReadADC(0);
		_delay_ms(1);
		// read next value en store in val2
		val2=ReadADC(0);
		char str[10];
		itoa(value1,str,10);
		USART_putstr(str);
		USART_putstr("\n");
		// SENSORVALUE can be changed, increasing will make it less sensitive. Decreasing will make it more sensitive
		if(value1-value2 > SENSORVALUE || value2-value1 > SENSORVALUE)
		{
			PORTC ^= 0b00000010; // LIGHT ON UC
			_delay_ms(200);
		}
	}
}
