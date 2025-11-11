#include "LPC17xx.h"
#include <stdio.h> // Added for sprintf

#define RS_CTRL (1 << 27) // Pin 27
#define EN_CTRL (1 << 28) // Pin 28
#define DT_CTRL 0x07800000 // Pins 23-26

unsigned long int temp1 = 0, temp2 = 0, i, j;
unsigned char flag1 = 0, flag2 = 0;
unsigned char msg1[] = {"Welcome"};
unsigned char msg2[] = {"to Manipal"};
char msg[20]; // Buffer for ADC converted string

long int x;

void lcd_write(void) {
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
    temp2 = (temp1 & 0xF0) << 19;
    port_write();
    if (!flag2) {
        temp2 = (temp1 & 0x0F) << 23;
        port_write();
    }
}
void port_write(void) {
    LPC_GPIO0->FIOCLR = DT_CTRL;
    LPC_GPIO0->FIOSET = temp2 & DT_CTRL;
    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = RS_CTRL;
    else
        LPC_GPIO0->FIOSET = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    delay_lcd(5000);
}

void delay_lcd(unsigned int count) {
    unsigned int r;
    for (r = 0; r < count * 1000; r++) {
        __NOP();
    }
}


unsigned long int init_command[] = {
    0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80
};

int main() {
    LPC_PINCON->PINSEL1 &= ~(3 << 30); // Clear bits for GPIO
    SystemInit();
    SystemCoreClockUpdate();
    LPC_GPIO0->FIODIR |= (DT_CTRL | RS_CTRL | EN_CTRL); // Configure pins as output
    flag1 = 0;
    for (i = 0; i < sizeof(init_command)/sizeof(init_command[0]); i++) {
        temp1 = init_command[i];
        lcd_write();
    }
    flag1 = 1;
    i = 0;
    while (msg1[i] != '\0') {
        temp1 = msg1[i];
        lcd_write();
        i++;
    }
    LPC_ADC->ADCR = (1 << 4) | (1 << 21) | (1 << 16);
    NVIC_EnableIRQ(ADC_IRQn);
    return 0;
}

void ADC_IRQHandler() {
    x = (LPC_ADC->ADGDR >> 4) & 0xFFF;
    sprintf(msg, "Value:%4ld", x);
    flag1 = 1;
    temp1 = 0xC0;
    lcd_write();
    i = 0;
    while (msg[i] != '\0') {
        temp1 = msg[i];
        lcd_write();
        i++;
    }
    i = 0;
    while (msg2[i] != '\0') {
        temp1 = msg2[i];
        lcd_write();
        i++;
    }
}
