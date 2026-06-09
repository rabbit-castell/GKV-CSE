#include <reg51.h>
#define cmdport P3
#define dataport P2
sbit rs=cmdport^0;
sbit rw=cmdport^1;
sbit e=cmdport^6;

void delay (int msec)
{
int i,j;
for(i=0; i<msec; i++)
for (j=0; j<1275; j++);
}

void lcdcmd (unsigned char item)
{
dataport= item;
rs=0;
rw=0;
e=1;
delay(1);
e=0;
}

void lcddata (unsigned char item)
{
dataport= item;
rs=1;
rw=0;
e=1;
delay(1);
e=0;
}


void main()
{
lcdcmd(0x38);
delay(100);
lcdcmd(0x0E);
delay(100);
lcdcmd(0x01);
delay(100);
lcdcmd(0x06);
delay(100);
lcdcmd(0x86);
delay(100);
lcddata('N');
delay(100);
	lcddata('A');
delay(100);
	lcddata('M');
delay(100);
	lcddata('E');
delay(100);
}