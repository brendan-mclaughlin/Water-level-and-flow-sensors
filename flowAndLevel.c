#include <stdint.h>
#include "lib/hd44780.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/IO_Macros.h"
#define F_CPU 16000000UL             // Setting CPU Frequency 16MHz

volatile int NbTopsFan; //measuring the rising edges of the signal
int calc = 0;
int ADC_O_1;                         // ADC Output First 8 bits 
int ADC_O_2;                         // ADC Output Next 2 bits  

ISR (INT1_vect)        //External interrupt_one ISR
{
        NbTopsFan++;
}



int main(void)
{

	LCD_Setup();

    DDRD &= ~(1 << PIND3);
    EICRA = (1<<ISC11) | (1<<ISC10);
    EIMSK = (1 << INT1);

    ADMUX = 0x40;
    ADCSRA = 0xC7;
     ADCSRB = 0x00;
    while(1){            

            NbTopsFan = 0; //Set NbTops to 0 ready for calculations
            int adcMax = 1023;                       
            int adcTotal = 0;

            sei();
            my_delay_ms(1000);
            cli(); //Disable interrupts
            calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour
            LCD_Clear();
            LCD_GotoXY(0, 0);
            LCD_PrintString("Flow(L/hr): ");

            LCD_PrintDouble(calc, 2); //
            LCD_GotoXY(0, 1);
             if ( (ADCSRA & 0x40) == 0)
                    { 
                        
                        ADC_O_1 = ADCL;
                        ADC_O_2 = ADCH;
                        adcTotal = ADC_O_1;
                        if(ADC_O_2 == 1 )
                            adcTotal += 256;
                        if(ADC_O_2 == 2 )
                            adcTotal += 512;
                        
                        LCD_PrintString("Level %: ");
                        int levelPercent; 
                        if(adcTotal < 300){
                            levelPercent =0;
                            
                        }
                        else if(adcTotal < 400){
                            levelPercent =10;
                        }
                        else if(adcTotal < 500){
                            levelPercent =30;
                        }
                         else if(adcTotal < 600){
                            levelPercent =50;
                        }
                        else if(adcTotal < 700){
                            levelPercent =60;
                        }
                         else if(adcTotal < 800){
                            levelPercent =70;
                        }
                        else if(adcTotal < 900){
                            levelPercent =80;
                        }
                        else{
                            levelPercent = 90;
                        }

                        LCD_PrintInteger(levelPercent);

                        ADCSRA |= 0x40;
                        _delay_ms(600);
                    }
                        } 

    }
    

void my_delay_ms(unsigned int delay) 
{
	unsigned int i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	for (i=0; i < (delay % 10); i++)
	{
		_delay_ms(1);
	}
}