#include <reg51.h>

#define port P3
#define dataport P2
#define key P1

sbit rs = port^0;
sbit rw = port^1;
sbit en = port^6;

sbit col1 = key^4;
sbit col2 = key^5;
sbit col3 = key^6;

// Standard delay function
void delay(unsigned int msec) {
    int i, j;
    for (i = 0; i < msec; i++)
        for (j = 0; j < 1275; j++);
}

// LCD Command function
void lcdcmd(unsigned char item) {
    dataport = item;
    rs = 0; rw = 0; en = 1;
    delay(1); en = 0;
}

// LCD Data function
void lcddata(unsigned char item) {
    dataport = item;
    rs = 1; rw = 0; en = 1;
    delay(1); en = 0;
}

// Initialize the LCD once at startup
void lcd_init() {
    lcdcmd(0x38); // 8-bit mode, 2 lines
    lcdcmd(0x0E); // Display ON, Cursor ON
    lcdcmd(0x01); // Clear Display
    lcdcmd(0x06); // Auto-increment cursor
}

// Clear screen and print the new string
void lcd_print(char *str) {
    lcdcmd(0x01); // Clear display so text doesn't overlap
    lcdcmd(0x80); // Force cursor to start of line 1
    
    while (*str != '\0') {
        lcddata(*str);
        str++;
        delay(10);
    }
}

void main() {
    // 1. A clean Lookup Table that mimics the physical keypad
    char *keypad_matrix[4][3] = {
        {"One 1", "Two 2", "Three 3"},
        {"Four 4", "Five 5", "Six 6"},
        {"Seven 7", "Eight 8", "Nine 9"},
        {"*", "Zero 0", "#"}
    };
    
    // 2. Hex values to ground one row at a time (Row 1 to 4)
    unsigned char row_mask[4] = {0xFE, 0xFD, 0xFB, 0xF7}; 
    int r;

    lcd_init();

    while (1) {
        key = 0xF0; // Set all Rows (P1.0-P1.3) LOW, and Cols (P1.4-P1.6) HIGH
        
        // Check if ANY button is pressed
        if (col1 == 0 || col2 == 0 || col3 == 0) {
            delay(20); // Debounce: Wait 20ms to ignore physical button noise
            
            // Loop through the 4 rows to find exactly which button it is
            for (r = 0; r < 4; r++) {
                key = row_mask[r]; // Ground current row
                
                // If a column drops to 0, match it with the row (r) to print the text
                if (col1 == 0) { lcd_print(keypad_matrix[r][0]); while(col1==0); }
                if (col2 == 0) { lcd_print(keypad_matrix[r][1]); while(col2==0); }
                if (col3 == 0) { lcd_print(keypad_matrix[r][2]); while(col3==0); }
            }
        }
    }
}