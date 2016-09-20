#include "multiservo.h"
uint initialValue[] = {1500,1500,1500,1500,1500,1500,1500,1500};						  
uint userValue[]    = {1500,1500,1500,1500,1500,1500,1500,1500};

uint COUNTVALUE[9];

sbit pwmPin1 = P1^0;
sbit pwmPin2 = P1^1;
sbit pwmPin3 = P1^2;
sbit pwmPin4 = P1^3;
sbit pwmPin5 = P1^4;
sbit pwmPin6 = P1^5;
sbit pwmPin7 = P1^6;
sbit pwmPin8 = P1^7;

void updateMultiServo(uint count_value[8])
{	
	uchar i = 0;
	uint tal = 0;
	uint temp = 0;
	for ( i = 0; i <8; i++)
	{
		temp = count_value[i];
		COUNTVALUE[i] = 65536 - temp;
		tal += count_value[i];
	}
		COUNTVALUE[8] = 65536-(18432 - tal);
}


void MultiServoInterrupt() interrupt 3	 using 3
{
	static uchar i = 1;
	switch(i)
	{
		case 1:
			TH1 = COUNTVALUE[0]>>8;
			TL1 = (COUNTVALUE[0]<<8)>>8;
			pwmPin1 = 1;
			break;
										 
		case 2:
			TH1 = COUNTVALUE[1]>>8;
			TL1 = (COUNTVALUE[1]<<8)>>8;
			pwmPin1 = 0;
			pwmPin2 = 1;
			break;
		case 3:
			TH1 = COUNTVALUE[2]>>8;
			TL1 = (COUNTVALUE[2]<<8)>>8;
			pwmPin2 = 0;
			pwmPin3 = 1;
			break;
										 
		case 4:
			TH1 = COUNTVALUE[3]>>8;
			TL1 = (COUNTVALUE[3]<<8)>>8;
			pwmPin3 = 0;
			pwmPin4 = 1;
			break;
		case 5:
			TH1 = COUNTVALUE[4]>>8;
			TL1 = (COUNTVALUE[4]<<8)>>8;
			pwmPin4 = 0;
			pwmPin5 = 1;
			break;
										 
		case 6:
			TH1 = COUNTVALUE[1]>>8;
			TL1 = (COUNTVALUE[1]<<8)>>8;
			pwmPin5 = 0;
			pwmPin6 = 1;
			break;
		case 7:
			TH1 = COUNTVALUE[2]>>8;
			TL1 = (COUNTVALUE[2]<<8)>>8;
			pwmPin6 = 0;
			pwmPin7 = 1;
			break;
										 
		case 8:
			TH1 = COUNTVALUE[3]>>8;
			TL1 = (COUNTVALUE[3]<<8)>>8;
			pwmPin7 = 0;
			pwmPin8 = 1;
			break;


		case 9:
			TH1 = COUNTVALUE[4]>>8;
			TL1 = (COUNTVALUE[4]<<8)>>8;
			pwmPin8 = 0;
			i = 0;
			break;
	}
	i += 1;
}
void MultiServoInit()
{
	TMOD |= 0x10;
	TH1 = 0;
	TL1 = 0;
	updateMultiServo(initialValue);
	//MultiServoWrite(initialValue);
	EA  = 1;
	ET1 = 1;
	TR1 = 1;
}




void change(uint va)
{
	uchar i = 8;
	for	(i = 0; i < 8; i++)
	{
		 userValue[i] = va;
	}
	updateMultiServo(userValue);
}
