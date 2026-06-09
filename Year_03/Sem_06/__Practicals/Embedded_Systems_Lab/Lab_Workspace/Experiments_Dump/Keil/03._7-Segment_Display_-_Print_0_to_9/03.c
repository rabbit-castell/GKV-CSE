#include <reg51.h>

// Standard hardware delay
void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void main()
{
    int i;
    
    // Use 'unsigned char' for 8-bit port data.
    // Adding the 'code' keyword tells Keil to store this array in ROM (Flash) 
    // instead of wasting the 8051's extremely tiny 128-byte RAM.
    unsigned char code num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
                                0x6D, 0x7D, 0x07, 0x7F, 0x67};

    // The infinite loop traps the microcontroller so it counts continuously
    while(1)
    {
        for(i = 0; i < 10; i++)
        {
            P2 = num[i];  // Output the hex value to the display
            delay(100);   // Wait so the human eye can read it
        }
    }
}