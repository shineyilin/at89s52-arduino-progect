#ifndef __COM_DEFINE_H__
#define __COM_DEFINE_H__
#include <AT89X52.h>

#define uchar unsigned char 
#define uint  unsigned int 

sbit led8 = P1^7;
sbit led7 = P1^6; 
sbit led6 = P1^5; 
sbit led5 = P1^4;
sbit led4 = P1^3;
sbit led3 = P1^2;
sbit led2 = P1^1;
sbit led1 = P1^0;

sbit IR_REC = P3^2;
sbit IR_SEN = P1^1;

sbit beep = P2^7;

#define leddua  P0
#define ledwei  P2

typedef struct 
{
	uchar ir_rec;
	int  ir_but;
	uchar ir_sen;
} IR_DATA;

#endif