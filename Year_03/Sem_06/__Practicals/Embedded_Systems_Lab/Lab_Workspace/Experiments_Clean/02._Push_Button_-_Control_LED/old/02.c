#include <reg51.h>

sbit button_on = P1^0;
sbit LED       = P2^0;

void main()
{
    LED = 0;

    while(1)
    {
        if(button_on == 0)
        {
            LED = 1;
        }
        else
        {
            LED = 0;
        }
    }
}