#include <reg51.h>

void delayms(int time)
{
    int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 1275; j++);
}

void main()
{
    int i;
    char num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                  0x6D, 0x7D, 0x07, 0x7F, 0x67};

    for(i = 0; i < 10; i++)
    {
        P2 = num[i];
        delayms(100);
    }
}