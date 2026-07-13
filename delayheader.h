#include<LPC21xx.H>
void delay_second(unsigned int);
void delay_ms(unsigned int);

void delay_second(unsigned int second)
{
	T0PR=15000000-1;
	T0TCR=0x01;
	while(T0TC<second);
	T0TCR=0x03;
	T0TCR=0x00;
}

void delay_ms(unsigned int ms)
{
	T0PR = 15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}

