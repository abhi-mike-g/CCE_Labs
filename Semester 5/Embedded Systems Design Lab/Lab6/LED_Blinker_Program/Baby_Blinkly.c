#include <LPC17xx.h>

int main() {

    LPC_PINCON->PINSEL2 &= 0x3FFFFFFF;
    LPC_PINCON->PINSEL3 &= 0xFFFF0000;

    LPC_GPIO1->FIODIR |= 0x00FF8000;

    while (1) {
        LPC_GPIO1->FIOSET = 0x00FF8000;
        LPC_GPIO1->FIOCLR = 0x00FF8000;
    }
}
