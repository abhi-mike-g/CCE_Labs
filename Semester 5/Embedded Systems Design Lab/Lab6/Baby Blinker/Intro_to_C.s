#include <LPC17xx.h>

int main() {

    LPC_PINCON->PINSEL0 &= 0xFF0000FF;
    LPC_PINCON->PINSEL1 &= 0xFFFFFF00;
    LPC_GPIO0->FIODIR |= 0x00000FF0;

    while (1) {
        LPC_GPIO0->FIOSET = 0x00000FF0;
        LPC_GPIO0->FIOCLR = 0x00000FF0;
    }
}
