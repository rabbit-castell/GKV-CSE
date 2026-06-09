#include <reg51.h>

// Standard hardware delay
void delay(unsigned int time) 
{
    unsigned int i, j;
    for(i = 0; i < time; i++) 
    {
        for(j = 0; j < 1275; j++); // Approx 1ms delay at 11.0592MHz/12MHz
    }
}

void main() 
{
    // Initialize ports to a known starting state
    P0 = 0x00; 
    P2 = 0xFF; 

    while(1) 
    {
        // Toggle all bits on both ports simultaneously
        P0 = ~P0; 
        P2 = ~P2; 
        
        delay(50); 
    }
}