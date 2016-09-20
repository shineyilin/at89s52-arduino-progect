#include "show.h"



uchar code duan[]=					//Êý×Ö0~9£¬
		       {0xc0,0xf9,0xa4,
			    0xb0,0x99,0x92,
				0x82,0xf8,0x80,
				0x90,0x88,0x83,0xc6,0xa1,0x86,
				0x8e};

uchar code wei[]={0xf7,0xfb,0xfd,0xfe};

void watchdog_init()
{
	TMOD = TMOD|0x01;
	TH0 = 0x4c;
	TL0 = 0x00;
	ET0 = 1;
	TR0 = 1;	
	EA  = 1;
}

void watchdog(void) interrupt 1
{
	 static uint time;
	 TH0 = 0xfe;
	 TL0 = 0x33;
	 time++;
	 led2 = ~led2;
	 if (time%200==0){ led1=~led1;}
}
void delayus(uint us) //us >2
{
	us /=2;
	while (--us);
}

void show(uint value)
{
	uchar temp;
	char i;
	for ( i = 0; i < 4; i++ )
	{
		temp   = value%10;
		value  = value/10;
		ledwei = (ledwei|0x0f)&wei[i];

		leddua = duan[temp];
		delayus(100);
		leddua = 0xff; 
		if (value == 0) break;
	
	}
}
