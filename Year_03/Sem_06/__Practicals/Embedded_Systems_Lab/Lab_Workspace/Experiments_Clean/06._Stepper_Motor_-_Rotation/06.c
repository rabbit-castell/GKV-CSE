#include <reg51.h>

void delay(int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 1275; j++);
    }
}

void main() {
    // UNCOMMENT ONLY ONE OF THESE AT A TIME:

    // 1. Wave drive (4 steps)
    int rot_angle[] = {0x08, 0x04, 0x02, 0x01};

    // 2. Full-step (4 steps)
    // int rot_angle[] = {0x0C, 0x06, 0x03, 0x09};

    // 3. Half-step (8 steps)
    // int rot_angle[] = {0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};

    int i;
    // Calculate the number of items in the array dynamically
    int num_steps = sizeof(rot_angle) / sizeof(rot_angle[0]);

    while(1) {
        // Now the loop automatically adjusts to 4 or 8!
        for(i = 0; i < num_steps; i++) {
            P1 = rot_angle[i];  
            delay(100);         
        }
    }
}