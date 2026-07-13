#include<LPC21XX.H>
#include "lcd1.c"
#include "delayheader.h"
#define M1 1<<3
#define M2 1<<4
#define M3 1<<6
#define M4 1<<7
#define LED1 1<<5

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_STR(unsigned char*);

int main()
{
	  unsigned char rxByte=0;
		UART0_CONFIG();
	  LCD_INIT();
	  IODIR0|= M1|M2|M3|M4|LED1;
		while(1)
		{
			rxByte=UART0_RX();
			if(rxByte=='A')
				{
					IOSET0=LED1;
					delay_ms(500);
					IOSET0=M1|M2|M3|M4;
					LCD_COMMAND(0x01);
					LCD_STR("START");
				}
			if(rxByte=='S')
			{
					IOCLR0=LED1;
					delay_ms(500);
				  IOCLR0=M1|M2|M3|M4;
				  LCD_COMMAND(0x01);
					LCD_STR("STOP");
			}
			if(rxByte=='F')
			{
				IOSET0=M1|M3;
				IOCLR0=M2|M4;
				LCD_COMMAND(0x01);
				LCD_STR("FORWARD");
			}
			if(rxByte=='B')
			{
				IOSET0=M2|M4;
				IOCLR0=M1|M3;
				LCD_COMMAND(0x01);
				LCD_STR("BACKWARD");
			}
		}
	}
	
	void UART0_CONFIG(void)
{
	PINSEL0 |=0x05;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}

void UART0_TX(unsigned char txByte)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=txByte;
}

void UART0_STR(unsigned char*s)
{
    while(*s)
		{
			UART0_TX(*s++);
		}
}

unsigned char UART0_RX(void)
{
	while((U0LSR&0x1)==0);
	return U0RBR;
}

