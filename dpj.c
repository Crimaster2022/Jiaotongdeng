#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar data buf[2];             //ÃëÏÔÊ¾µÄ±äÁ¿
char data sec;        

int dx_nb=0;
uchar data count;   //¶¨Ê±Æ÷ÖÐ¶Ï´ÎÊý

sbit Red_nb=P2^6;             //ÄÏ±±ºìµÆ±êÖ¾
sbit Yellow_nb=P2^5;          //ÄÏ±±»ÆµÆ±êÖ¾
sbit Green_nb=P2^4;           //ÄÏ±±ÂÌµÆ±êÖ¾.

sbit Red_dx=P2^3;             //¶«Î÷ºìµÆ±êÖ¾
sbit Yellow_dx=P2^2;         //¶«Î÷»ÆµÆ±êÖ¾
sbit Green_dx=P2^1;          //¶«Î÷ÂÌµÆ±êÖ¾

uchar code table[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};  //¹²Ñô¼«×ÖÐÍÂë


//º¯ÊýµÄÉùÃ÷²¿·Ö
void delay(int ms);
void display();

//Ö÷³ÌÐò
void main()
{
	TMOD=0x01;
	TH0=0xDC;
	TL0=0x00;
	EA=1;
	ET0=1;
	TR0=1;
	P2=0xbd;
	sec=80;
	while(1)
	{ 
		  display();    
	} 
}

void display(void)         //ÏÔÊ¾×Ó³ÌÐò
{
	buf[1]=sec/10;
	buf[0]=sec%10;
	P1=0x00;
	P0=0xff;
	P1=0x01;
	P0=table[buf[1]];
	delay(1) ;
	P1=0x00;
	P0=0xff;
	P1=0x02;
	P0=table[buf[0]];
	delay(1);
	P1=0x00;
	P0=0xff;
	P1=0X04;
	P0=table[buf[1]];
	delay(1);
	P1=0x00;
	P0=0xff;
	P1=0X08;
	P0=table[buf[0]];
	delay(1);
} 

void time0(void) interrupt 1 using 1     
{          
      TH0=0xDC;                                      
      TL0=0x00;  //10ms
	  count++;
	  if(count==100)  //1sÊ±¼äµ½
			{
				count=0;
				sec--;
         	    if((sec<4)&&(sec>=0)&&(dx_nb==0))
					{
						Green_dx=1; 
						Yellow_dx=0;
					}
				else if((sec<4)&&(sec>=0)&&(dx_nb==1))
					{
						Green_nb=1; 
						Yellow_nb=0;
					}
				if((dx_nb==0)&&(sec<0))
					{
						P2=0xe7;
						dx_nb=!dx_nb;
						sec=60;
					}
				else if((dx_nb==1)&&(sec<0))
					{
						P2=0xbd;
						dx_nb=!dx_nb;
			   		    sec=80;
					}
	        }
}
 
void delay(int ms)
{
	uint j,k;
	for(j=0; j<ms; j++)
		for(k=0;k<124;k++);
}

