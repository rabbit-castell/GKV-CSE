#include <reg51.h>

sbit LED = P1^5; // Define LED at P1.5
unsigned char count = 0;

void timer0_ISR(void) interrupt 1 { 
    // Reload timer values for next 50ms
    TH0 = 0x3C;
    TL0 = 0xB0;
    count++;
    
    // Toggle LED after 1 second (20 * 50ms = 1000ms = 1s)
    if (count >= 20) {
        LED = ~LED; // Toggle LED
        count = 0;  // Reset counter
    }
}

void main() {
    TMOD = 0x01; // Timer 0, Mode 1 (16-bit mode)
    
    TH0 = 0x3C;  // Load initial value (High byte)
    TL0 = 0xB0;  // Load initial value (Low byte)
    
    EA = 1;      // Enable Global Interrupts
    ET0 = 1;     // Enable Timer 0 Interrupt
    TR0 = 1;     // Start Timer 0
    
    while(1);    // Infinite loop, MCU waits for interrupts
}