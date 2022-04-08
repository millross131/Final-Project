/*
 * GccApplication1.c
 *
 * Created: 4/1/2022 7:53:35 PM
 * Author : millross
 */ 

#include <avr/io.h>


int main(void)
{
	DDRC = 0xFF;
    /*Skeleton code for clap*/
    if(microphone hears clap){
		PORTC = 0xFF;
	}
	/*Skeleton code for temp sensor*/
	if(temp sensor val >= 80){
		set bulb color to red 
	}
	else if(temp sensor val < 80 && temp sensor val > 65){
		set bulb color to yellow
	}
	else if(temp sensor val <= 65 && temp sensor val){
		set bulb color to blue
	}
	/*Skeleton code for remote*/
	if(power button pressed){
		if(PORTC == 0xFF){
			PORTC = 0;
		}
		else{
			PORTC = 0xFF;
		}
	}
	if(1 is pressed){
		if(normal mode){
			go to temp mode
		}
		else{
			go to normal mode
		}
	}
	/*Skeleton code for alarm and lights on*/
	(if user wakeup t == real clk t){
		buzzer on
		slowly turn lights on 
	} 
}

