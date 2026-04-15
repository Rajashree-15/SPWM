/*
 * main.c
 *
 *  Created on: 31-July-2022
 *      Author: Rajashree
 */
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#define PORTx      PORTD
uint8_t sine_phase1[]={0X7F	,0X84	,0X89	,0X8E	,0X93	,0X98	,0X9D	,0XA2	,0XA7	,0XAC	,0XB1	,0XB5	,0XBA	,0XBE	,0XC3	,0XC7
		,0XCB	,0XCF	,0XD3	,0XD7	,0XDB	,0XDE	,0XE1	,0XE5	,0XE8	,0XEA	,0XED	,0XEF	,0XF2	,0XF4	,0XF6	,0XF7	,0XF9	,0XFA
		,0XFB	,0XFC	,0XFD	,0XFE	,0XFE	,0XFE	,0XFE	,0XFE	,0XFD	,0XFC	,0XFB	,0XFA	,0XF9	,0XF7	,0XF6	,0XF4	,0XF2	,0XEF
		,0XED   ,0XEA	,0XE8	,0XE5	,0XE1	,0XDE	,0XDB	,0XD7	,0XD3	,0XCF	,0XCB	,0XC7	,0XC3	,0XBF	,0XBA	,0XB5	,0XB1	,0XAC
		,0XA7   ,0XA2	,0X9D	,0X98	,0X93	,0X8E	,0X89	,0X84	,0X7F	,0X7A	,0X75	,0X70	,0X6B	,0X66	,0X61	,0X5C	,0X57	,0X52
		,0X4D	,0X49	,0X44	,0X40	,0X3B	,0X37	,0X33	,0X2F	,0X2B	,0X27	,0X23	,0X20	,0X1D	,0X19	,0X16	,0X14	,0X11	,0X0F
		,0X0C	,0X0A	,0X8	,0X7	,0X5	,0X4	,0X3	,0X2	,0X1	,0X0	,0X0	,0X0	,0X0	,0X0	,0X1	,0X2	,0X3	,0X4
		,0X5	,0X7	,0X8	,0X0A	,0X0C	,0X0F	,0X11	,0X14	,0X16	,0X19	,0X1D	,0X20	,0X23	,0X27	,0X2B	,0X2F	,0X33	,0X37
		,0X3B	,0X3F	,0X44	,0X49	,0X4D	,0X52	,0X57	,0X5C	,0X61	,0X66	,0X6B	,0X70	,0X75	,0X7A};
const length=sizeof(sine_phase1);uint8_t k1=0,k2=53,k3=105;
void PWM_init ()
 {
	    DDRD |= _BV(PD6) |_BV(PD5)|_BV(PD3)|_BV(PD2)|_BV(PD7)|_BV(PD4);
 		DDRB |= _BV(PB2);
 		PORTD |= (1<<PORTD4) | (1<<PORTD7);

 		//TIMER2  fast PWM Mode
 		TCCR2B  = (0<<CS20)|(1<<CS21)|(0<<CS22);//N=8 F=7.8KHZ
 		TCCR2A =_BV(COM2B1)|_BV(WGM20)|_BV(WGM21);

 		//TIMER 0 fast PWM Mode
 		TCCR0B = (0<<CS00)|(1<<CS01)|(0<<CS02);//N=8
 		TCCR0A = _BV(WGM00)|_BV(WGM01)|_BV(COM0B1)|_BV(COM0A1);

 		//TIMER1 ISR fISR = 7.8khz fast PWM mode
 		TCCR1B =_BV(CS11)|_BV(WGM12);
 		TCCR1A =_BV(COM1B0)|_BV(COM1B1)|_BV(WGM10);//Toggle on Comp match


 		TIMSK1 =(1<<OCIE1B);
 		sei();//Enabling the global interrupts
 		OCR1B = 0X7C;
 		OCR1A = 0X7C;
}
//Fix frequency of sinewave, no of samples in sinewave (or no of steps in the step sine wave) and calculate the frequency of ISR
int main()
{
PWM_init();
while(1)
{
}
return 0;
}
ISR(TIMER1_COMPB_vect)//PWM2 RED **
{
	float amp=0.9;
	OCR2B=(sine_phase1[k1]*amp);//4096);
	OCR0A=(sine_phase1[k2]*amp);//4096);
	OCR0B=(sine_phase1[k3]*amp);//4096);
	k1++;k2++;k3++;
	if(k1>=length)
		k1=0;
	if(k2>=length)
		k2=0;
	if(k3>=length)
		k3=0;
}
