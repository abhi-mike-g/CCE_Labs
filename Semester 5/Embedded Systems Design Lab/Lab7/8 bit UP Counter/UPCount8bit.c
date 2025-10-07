#include <LPC17xx.h>

void delay(void) {
    for (volatile int i = 0; i < 100000; i++);
}

int main(void) {
    unsigned int count = 0;

    LPC_PINCON->PINSEL1 &= 0x0000FFFF;
    LPC_GPIO0->FIODIR  |= 0x007F8000;

    while (1) {
        LPC_GPIO0->FIOCLR = 0x007F8000;

        LPC_GPIO0->FIOSET = (count << 15) & 0x007F8000;

        delay();

        count++;
        if (count == 256) {
            count = 0;
        }
    }
}
