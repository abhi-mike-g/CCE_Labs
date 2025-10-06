#include <LPC17xx.h>

unsigned int seg_code[16] = {
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
    0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71
};

void delay_display(void) {
    for (volatile int i = 0; i < 1000; i++); // short refresh delay for multiplexing
}

void display_number(unsigned int num) {
    unsigned int digits[4];
    digits[0] = num & 0xF;
    digits[1] = (num >> 4) & 0xF;
    digits[2] = (num >> 8) & 0xF;
    digits[3] = (num >> 12) & 0xF;

    for (int i = 0; i < 4; i++) {
        // Output segment pattern
        LPC_GPIO0->FIOCLR = 0x00000FF0;  // Clear P0.4–P0.11
        LPC_GPIO0->FIOSET = (seg_code[digits[i]] << 4);

        // Enable one digit at a time (active LOW)
        LPC_GPIO2->FIOPIN = (LPC_GPIO2->FIOPIN & ~0x0F) | (~(1 << i) & 0x0F);

        delay_display();
    }
}

void timer0_init(void) {
    LPC_SC->PCONP |= (1 << 1);       // Power to Timer0
    LPC_SC->PCLKSEL0 &= ~(3 << 2);   // PCLK = CCLK/4
    LPC_TIM0->PR = 3000000 - 1;      // For 1 Hz at 12 MHz PCLK
    LPC_TIM0->MR0 = 1;              // Match every 1 sec
    LPC_TIM0->MCR = 0x04;           // Reset on MR0
    LPC_TIM0->TCR = 0x01;           // Enable timer
}

int timer0_flag(void) {
    if (LPC_TIM0->TC >= 1) {
        LPC_TIM0->TC = 0;  // manually reset
        return 1;
    }
    return 0;
}

int main(void) {
    unsigned int count = 0;
    unsigned int key;

    // Segment pins P0.4–P0.11 as GPIO
    LPC_PINCON->PINSEL0 &= 0xFF00000F;
    LPC_GPIO0->FIODIR  |= 0x00000FF0;

    // Digit select P2.0–P2.3 as output
    LPC_PINCON->PINSEL4 &= ~0x000000FF;
    LPC_GPIO2->FIODIR  |= 0x0000000F;

    // Switch P2.12 as input
    LPC_PINCON->PINSEL4 &= ~(3 << 24);
    LPC_GPIO2->FIODIR  &= ~(1 << 12);

    timer0_init();

    while (1) {
        // Refresh display continuously
        display_number(count);

        // Check 1-second interval
        if (timer0_flag()) {
            // Read switch (Up/Down)
            key = (LPC_GPIO2->FIOPIN >> 12) & 0x01;

            if (key == 1) {
                // Up counter
                count++;
                if (count > 0xFFFF) count = 0;
            } else {
                // Down counter
                if (count == 0)
                    count = 0xFFFF;
                else
                    count--;
            }
        }
    }
}
