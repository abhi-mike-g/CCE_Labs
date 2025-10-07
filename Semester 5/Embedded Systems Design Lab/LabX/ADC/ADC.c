#include <LPC17xx.h>

void TIMER0_IRQHandler(void);

int main(void) {
    // Configure P0.5 as GPIO output
    LPC_PINCON->PINSEL0 &= ~(3 << 10);        // P0.5 = GPIO (bits 11:10)
    LPC_GPIO0->FIODIR   |= (1 << 5);          // P0.5 as output

    // Power up Timer 0 (most systems do this by default)
    LPC_SC->PCONP |= (1 << 1);

    // Timer0 configuration
    LPC_TIM0->PR  = 0;            // No prescaler, increment TC every PCLK
    LPC_TIM0->MR0 = 5000000;      // Match Register 0 value (adjust for ~toggle rate)
    LPC_TIM0->MCR = (1 << 0) | (1 << 1);   // Interrupt and reset on MR0
    LPC_TIM0->TCR = 2;            // Reset Timer
    LPC_TIM0->TCR = 1;            // Enable Timer

    NVIC_EnableIRQ(TIMER0_IRQn);  // Enable Timer0 IRQ

    while (1) {
        // Do nothing, wait for interrupt
    }
}

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & 1) {              // Check interrupt flag for MR0
        LPC_TIM0->IR = 1;                // Clear interrupt flag
        LPC_GPIO0->FIOPIN ^= (1 << 5);   // Toggle P0.5 (LED ON/OFF)
    }
}
