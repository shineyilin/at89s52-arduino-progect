#include "include.h"


sbit pwmButtonAdd   = P3^3;
sbit pwmButtonDec   = P3^2;



uint val = 32778;
void init_Ultra()
{
	TMOD |= 0x50; 
	TH0 = 0;
	TL0 = 0;
	ET1 = 1;
	TR1 = 0;
	EA  = 1;
	TR1 = 0;
	
}


sbit ultraTrigPin = P1^4;				
sbit ultraEchoPin = P1^5;

uint length()
{
	uint count = TH1*256+TL1;
	TH1 = 0;
	TL1 = 0;
	ultraTrigPin = 0;				
	ultraEchoPin = 0;
	return count*340/100;
}

uint ultraRead()
{
	ultraTrigPin = 0;
	delayus(2);
	ultraTrigPin = 1;
	delayus(10);
	ultraTrigPin = 0;
	TR1 = 1;
	while(ultraEchoPin == 1);
	TR1 = 0;
	return length();
	 
}


void main()
{
	watchdog_init();
	MultiServoInit();
	//Uart_Init();
	//IR_Init();

	while(1)
	{
		//val = ultraRead();
		show(val/10);
		if (pwmButtonAdd == 0 && val<65520)
		{
			val += 10;
			change(val);
		}
		
		if (pwmButtonDec == 0 && val>10)
		{
			val -= 10;
			change(val);
		}
	}
}