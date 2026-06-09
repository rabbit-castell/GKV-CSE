#include <reg51.h>

#define cmdport P3
#define dataport P2

// --- LCD Control Pin Definitions ---
sbit rs = cmdport^0; // Register Select: 0 = Command Mode (setup), 1 = Data Mode (text)
sbit rw = cmdport^1; // Read/Write: 0 = Write to LCD, 1 = Read from LCD
sbit en = cmdport^6; // Enable: Needs a quick High-to-Low pulse to lock in the data

// Standard hardware delay
void delay(unsigned int msec) 
{
    unsigned int i, j;
    for(i = 0; i < msec; i++) 
    {
        for(j = 0; j < 1275; j++); // Approx 1ms delay at 11.0592MHz/12MHz
    }
}

// Send a configuration command (like clear screen, set cursor) to the LCD
void lcdcmd(unsigned char item) 
{
    dataport = item;
    rs = 0;  // Set to Command Mode
    rw = 0;  // Set to Write
    en = 1;  // Pull Enable High
    delay(1); 
    en = 0;  // Pull Enable Low (This falling edge locks the command into the LCD)
}

// Send actual text characters to the LCD
void lcddata(unsigned char item) 
{
    dataport = item;
    rs = 1;  // Set to Data Mode (Text)
    rw = 0;  // Set to Write
    en = 1;  // Pull Enable High
    delay(1); 
    en = 0;  // Pull Enable Low (This falling edge prints the character)
}

void main() 
{
    // LCD Initialization Sequence
    lcdcmd(0x38); delay(100); // Wakes up LCD: 8-bit mode, 2 lines, 5x7 font matrix
    lcdcmd(0x0E); delay(100); // Display ON, Cursor ON (Blinking)
    lcdcmd(0x01); delay(100); // Clear Display Screen completely
    lcdcmd(0x06); delay(100); // Entry Mode: Auto-increment cursor to the right
    lcdcmd(0x86); delay(100); // Move cursor to Line 1, Position 6
    
    // Displaying Message: "NAME"
    lcddata('N'); delay(100);
    lcddata('A'); delay(100);
    lcddata('M'); delay(100);
    lcddata('E'); delay(100);
    
    // Infinite loop safely traps the microcontroller so it doesn't restart and flicker
    while(1); 
}