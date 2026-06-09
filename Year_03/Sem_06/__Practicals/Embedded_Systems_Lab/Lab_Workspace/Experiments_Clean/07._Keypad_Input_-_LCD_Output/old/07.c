#include <reg51.h>
#define port P3   //port for LCD command
#define dataport P2  //port for LCD
#define key P1  //Port for Keypad
sbit rs=port^0;
sbit rw=port^1;
sbit en=port^6;

sbit col1=key^4;
sbit col2=key^5;
sbit col3=key^6;
sbit row1=key^0;
sbit row2=key^1;
sbit row3=key^2;
sbit row4=key^3;

void delay (unsigned int msec)
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
en=1;
delay(1);
en=0;
	return;
}

void lcddata (unsigned char item)
{
dataport= item;
rs=1;
rw=0;
en=1;
delay(1);
en=0;
	return;
}


void lcd_data_string(unsigned char *str) //function to send string on LCD
{	
int i=0;
while(str[i]!='\0')
{
lcddata(str[i]);
i++;
delay(10);
}
return;
}

void lcd(unsigned char str[10])  //function to initialize LCD
{
lcdcmd(0x38);
lcdcmd(0x0e);
lcdcmd(0x01);
lcdcmd(0x82);
lcd_data_string(str);
}


void display(int a) //function to display LCD
{
switch(a)
{
case 1:lcd("one 1");
break;
case 2:lcd("two 2");
break;
case 3:lcd("three 3");
break;
case 4:lcd("four 4");
break;
case 5:lcd("five 5");
break;
case 6:lcd("six 6");
break;
case 7:lcd("seven 7");
break;
case 8:lcd("eight 8");
break;
case 9:lcd("nine 9");
break;
case 10:lcd("Zero 0");
break;
case 11:lcd("*");
break;
case 12:lcd("#");
break;
}
}

void check_col1() //function for checking column one
{
row1=row2=row3=row4=1;
row1=0;
if(col1==0)
display(1);
row1=1;
row2=0;
if(col1==0)
display(4);
row2=1;
row3=0;
if(col1==0)
display(7);
row3=1;
row4=0;
if(col1==0)
display(11);
row4=1;
}

void check_col2() //function for checking column two
{
row1=row2=row3=row4=1;
row1=0;
if(col2==0)
display(2);
row1=1;
row2=0;
if(col2==0)
display(5);
row2=1;
row3=0;
if(col2==0)
display(8);
row3=1;
row4=0;
if(col2==0)
display(10);
row4=1;
}

void check_col3() //function for checking column three
{
row1=row2=row3=row4=1;
row1=0;
if(col3==0)
display(3);
row1=1;
row2=0;
if(col3==0)
display(6);
row2=1;
row3=0;
if(col3==0)
display(9);
row3=1;
row4=0;
if(col3==0)
display(12);
row4=1;
}

void main()
{
col1=col2=col3=1;
while(1)
{
row1=row2=row3=row4=0;
if(col1==0)
check_col1();
else
if(col2==0)
check_col2();
else
if(col3==0)
check_col3();
}
}