#include <LPC17xx.h>

void delay(void) {
    int i;
    for (i = 0; i < 500000; i++);
}

int main(void) {

    LPC_PINCON->PINSEL2 &= 0x3FFFFFFF;
    LPC_PINCON->PINSEL3 &= 0xFFFF0000;

    LPC_GPIO1->FIODIR |= 0x00FF8000;

    unsigned char pattern = 0x00; 
    int i;

    while (1) {
        for (i = 0; i < 16; i++) { 
            LPC_GPIO1->FIOPIN = (pattern << 15);

            delay();
            
            unsigned char feedback = (~(pattern >> 7)) & 0x01;
            pattern = (pattern << 1) | feedback;

            pattern &= 0xFF;
        }
    }
}
