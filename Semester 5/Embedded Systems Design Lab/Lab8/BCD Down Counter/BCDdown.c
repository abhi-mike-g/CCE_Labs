#include <LPC17xx.h>

unsigned int seg_code[10] = {
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};

int digits[4] = {9, 9, 9, 9};   // Start from 9999

void short_delay(void) {
    for (volatile int i = 0; i < 1000; i++);   // short refresh delay
}

void display_number(void) {
    for (int i = 0; i < 4; i++) {
        // Clear previous segment outputs
        LPC_GPIO0->FIOCLR = 0x00000FF0;
        // Output segment code for the digit
        LPC_GPIO0->FIOSET = (seg_code[digits[i]] << 4);

        // Enable the i-th digit (active LOW)
        LPC_GPIO2->FIOPIN = (LPC_GPIO2->FIOPIN & ~0x0F) | (~(1 << i) & 0x0F);

        short_delay();
    }
}

void timer0_init(void) {
    LPC_SC->PCONP |= (1 << 1);       // Power Timer0
    LPC_SC->PCLKSEL0 &= ~(3 << 2);   // PCLK = CCLK/4
    LPC_TIM0->PR = 3000000 - 1;      // 1 Hz at 12 MHz PCLK
    LPC_TIM0->MR0 = 1;
    LPC_TIM0->MCR = 0x04;           // Reset on MR0
    LPC_TIM0->TCR = 0x01;           // Enable timer
}

int timer0_flag(void) {
    if (LPC_TIM0->TC >= 1) {
        LPC_TIM0->TC = 0;
        return 1;
    }
    return 0;
}

void decrement_bcd(void) {
    if (digits[0] > 0) {
        digits[0]--;
    } else {
        digits[0] = 9;
        if (digits[1] > 0) {
            digits[1]--;
        } else {
            digits[1] = 9;
            if (digits[2] > 0) {
                digits[2]--;
            } else {
                digits[2] = 9;
                if (digits[3] > 0) {
                    digits[3]--;
                } else {
                    // Counter reached 0000 → reset to 9999 (or stop)
                    digits[0] = 9;
                    digits[1] = 9;
                    digits[2] = 9;
                    digits[3] = 9;
                }
            }
        }
    }
}

int main(void) {
    // Configure segment pins P0.4–P0.11 as GPIO output
    LPC_PINCON->PINSEL0 &= 0xFF00000F;
    LPC_GPIO0->FIODIR  |= 0x00000FF0;

    // Configure digit select pins P2.0–P2.3 as GPIO output
    LPC_PINCON->PINSEL4 &= ~0x000000FF;
    LPC_GPIO2->FIODIR  |= 0x0000000F;

    timer0_init();

    while (1) {
        display_number();

        if (timer0_flag()) {
            decrement_bcd();
        }
    }
}
