#include <reg51.h>

// Define hardware connections (capitalized for constants/hardware pins)
sbit BUTTON = P1^0;
sbit LED    = P2^0;

void main()
{
    // 1. CRITICAL: Configure the button pin as an INPUT
    BUTTON = 1; 
    
    // 2. Initialize LED to OFF
    LED = 0;

    while(1)
    {
        // 3. Directly invert the button state to control the LED
        // If BUTTON is 0 (pressed), LED becomes 1 (ON).
        // If BUTTON is 1 (released), LED becomes 0 (OFF).
        LED = ~BUTTON; 
    }
}