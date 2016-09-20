#include "ir_func.h"
#include "show.h"
#include "uart.h"
//sbit IR_REC = P3^2;

IR_DATA ir_value;

void delay70us(unsigned char x)    //x*0.07MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}

static void IR_Read(void) interrupt 0
{
	uchar i;
	uchar j;
	uchar n;
	uchar value[4]=0;
	EX0 = 0;
	
	led8 = 1;
	led7 = 1;

	delay70us(10);
			
	if (IR_REC==1) {EX0 = 1;return;}
	led8 = 0;
	while (IR_REC==0)	delay70us(1);
	while(IR_REC);	
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<8; j++)
		{

	 //=0
			while(!IR_REC)	delay70us(1);	
			while(IR_REC)
			{
				delay70us(1);
				n++;
			
				if (n>30){led7 =0;break;}
			}
			value[i] >>= 1; 
			if (n>10) value[i] |=0x80;
			n = 0;
		}
	}
	if (value[2]!=~value[3])
	{
		EX0 = 1;
		return;
	}
	
	ir_value.ir_rec = value[2];
	//putchar(ir_value.ir_rec);
	switch(value[2])    //ÅÐ¶Ï°´¼ü¼üÂëÖµ
	{
		case 0x16:ir_value.ir_but=0;break;  
		case 0x0c:ir_value.ir_but=1;break;   
		case 0x18:ir_value.ir_but=2;break;   
		case 0x5e:ir_value.ir_but=3;break;  
		case 0x08:ir_value.ir_but=4;break;   
		case 0x1c:ir_value.ir_but=5;break;   
		case 0x5a:ir_value.ir_but=6;break;   
		case 0x42:ir_value.ir_but=7;break;   
		case 0x52:ir_value.ir_but=8;break;   
		case 0x4a:ir_value.ir_but=9;break;   
	
		default :break; 
	}
	printf("%d\n",ir_value.ir_but);
	EX0 = 1;
}


void IR_Write(uchar value)
{
	char i;
	IR_SEN = 0;
	delayus(2);
	for (i = 0; i<8; i++)
	{
		IR_SEN = value&0x01;
		delayus(2);
		value >>= 1;
	}
	IR_SEN = 1;
}

void IR_Init()
{
	IT0 = 1;
	EA = 1;
	EX0 = 1;
}