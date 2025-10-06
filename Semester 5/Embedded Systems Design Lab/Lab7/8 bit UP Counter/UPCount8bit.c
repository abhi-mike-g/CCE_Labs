#include <LPC17xx.h>

void delay(void) {
    for (volatile int i = 0; i < 100000; i++);   // crude delay
}

int main(void) {
    unsigned int count = 0;

    // 1. Configure P0.15–P0.22 as GPIO output for LEDs
    LPC_PINCON->PINSEL1 &= 0x0000FFFF;   // P0.15–P0.22 as GPIO
    LPC_GPIO0->FIODIR  |= 0x007F8000;    // set as output

    while (1) {
        // 2. Clear previous LED output
        LPC_GPIO0->FIOCLR = 0x007F8000;

        // 3. Output counter value on LEDs
        LPC_GPIO0->FIOSET = (count << 15) & 0x007F8000;

        // 4. Delay for visibility
        delay();

        // 5. Increment counter (8-bit)
        count++;
        if (count == 256) {   // roll over after 8 bits
            count = 0;
        }
    }
}
