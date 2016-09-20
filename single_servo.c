#include "single_servo.h"

sbit pwmPin = P1^7;

uint  initialValueHigh;
uint  initialValueLow;
bit  pwmFlag;

int value20000 = 18432;

void ServoWrite(uint initialValueIn)
{
	initialValueHigh = 65536-initialValueIn;
	initialValueLow  = 65536-(18432-initialValueIn);

}
 
void ServoInit()
{
	TMOD |= 0x10;
	TH1 = 0;
	TL1 = 0;
	pwmFlag = 0;
	ServoWrite(1500);
	EA  = 1;
	ET1 = 1;
	TR1 = 1;

}

void pwmInterrupt() //interrupt 3	 using 2
{
	if (pwmFlag == 0)
	{
		TH1 = initialValueLow>>8;
		TL1 = (initialValueLow<<8)>>8;
		pwmPin   = ~pwmPin;
		pwmFlag = ~pwmFlag;
		return;
	}
	
	if (pwmFlag == 1)
	{
		TH1 = initialValueHigh>>8;
		TL1 = (initialValueHigh<<8)>>8;
		pwmPin   = ~pwmPin;
		pwmFlag  = ~pwmFlag;
		return;
	}
}
