#include <LPC17xx.h>

void delay(void) {
    for (volatile int i = 0; i < 100000; i++);   // crude delay
}

int main(void) {
    unsigned int count = 0;
    unsigned int key;

    // 1. Configure LED pins (P0.15–P0.22) as GPIO outputs
    LPC_PINCON->PINSEL1 &= 0x0000FFFF;    // P0.15–P0.22 as GPIO
    LPC_GPIO0->FIODIR  |= 0x007F8000;     // set as output

    // 2. Configure SW2 (P2.12) as GPIO input
    LPC_PINCON->PINSEL4 &= ~(3 << 24);    // P2.12 as GPIO
    LPC_GPIO2->FIODIR  &= ~(1 << 12);     // input

    while (1) {
        // 3. Read the switch
        key = (LPC_GPIO2->FIOPIN >> 12) & 0x01;

        // 4. Clear LED outputs
        LPC_GPIO0->FIOCLR = 0x007F8000;

        // 5. Display current counter value on LEDs
        LPC_GPIO0->FIOSET = (count << 15) & 0x007F8000;

        delay();

        // 6. Increment or Decrement depending on switch
        if (key == 1) {
            // SW2 not pressed → Up Counter
            count++;
            if (count == 256) count = 0;  // rollover after 8 bits
        } else {
            // SW2 pressed → Down Counter
            if (count == 0)
                count = 255;             // underflow wrap
            else
                count--;
        }
    }
}
