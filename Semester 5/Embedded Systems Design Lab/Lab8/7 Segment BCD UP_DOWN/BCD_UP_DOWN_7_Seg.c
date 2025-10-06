#include "LPC17xx.h"
#include <stdbool.h>

unsigned char seg7[] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};

#define SEG_PORT   LPC_GPIO0->FIOPIN
#define DIG_PORT   LPC_GPIO1->FIOPIN

unsigned int counter = 0;
bool count_up = true;

void delay_1sec() {
    volatile int i;
    for (i = 0; i < 5000000; i++);
}

void display_digit(unsigned char digit, unsigned char position) {
    DIG_PORT &= ~(1 << position);
    SEG_PORT = seg7[digit];
    delay_1sec();
    DIG_PORT |= (1 << position);
}

void update_counter() {
    unsigned char thousands, hundreds, tens, ones;
    
    thousands = (counter / 1000) % 10;
    hundreds = (counter / 100) % 10;
    tens = (counter / 10) % 10;
    ones = counter % 10;

    display_digit(thousands, 0);
    display_digit(hundreds, 1);
    display_digit(tens, 2);
    display_digit(ones, 3);
}

void EINT0_IRQHandler(void) {
    count_up = !count_up;
    LPC_GPIOINT->IO0IntClr = (1 << 0);
}

void TIMER0_IRQHandler(void) {
    LPC_TIM0->IR = 1;
    LPC_TIM0->TC = 0;
}

void setup_timer() {
    LPC_SC->PCONP |= (1 << 1);
    LPC_TIM0->PR = 0;
    LPC_TIM0->MR0 = 1000000;
    LPC_TIM0->MCR = (1 << 0) | (1 << 1);
    LPC_TIM0->TCR = 1;

    NVIC_EnableIRQ(TIMER0_IRQn);
}

void setup_gpio() {
    LPC_GPIO0->FIODIR = 0xFF;
    LPC_GPIO1->FIODIR = 0x0F;

    LPC_GPIOINT->IO0IntEnR = (1 << 0);
    NVIC_EnableIRQ(EINT0_IRQn);
}

int main() {
    setup_gpio();
    setup_timer();

    while (1) {
        if (count_up) {
            if (counter < 9999) {
                counter++;
            }
        } else {
            if (counter > 0) {
                counter--;
            }
        }

        update_counter();
        delay_1sec();
    }

    return 0;
}
