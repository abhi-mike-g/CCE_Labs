#include "LPC17xx.h"
#include <stdio.h>
#define RS_CTRL (1 << 27)    // P0.27
#define EN_CTRL (1 << 28)    // P0.28
#define DT_CTRL 0x07800000   // P0.23 to P0.26 (bits 23-26)
volatile uint8_t dice_number = 0;
volatile int seed = 1234;
#define ROW_PORT LPC_GPIO1
#define COL_PORT LPC_GPIO1
const uint8_t row_pins[4] = {20, 21, 22, 23};
const uint8_t col_pins[4] = {24, 25, 26, 27};
const unsigned long init_command[] = {
    0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80
};
unsigned long temp1 = 0, temp2 = 0;
unsigned char flag1 = 0, flag2 = 0;
void random_seed(void) {
    counter++;
    seed = (seed + counter * 3) % 65536;
}
int random_num(int max) {
    seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
    return (seed % max) + 1;
}
void EINT0_IRQHandler(void) {
    if (LPC_GPIOINT->IO2IntStatF & (1 << 10)) {
        delay_lcd(50);
        random_seed();
        dice_number = random_num(6);
        lcd_clear();
        lcd_print("Dice Roll:");
        lcd_set_cursor(1, 0);
        char buffer[3];
        sprintf(buffer, "%d", dice_number);
        lcd_print(buffer);
        LPC_GPIOINT->IO2IntClr = (1 << 10);
        LPC_SC->EXTINT |= 0x1;
    }
}
void keypad_init(void) {
    int i;
    uint32_t pin;
    uint32_t pinmode_shift;
    for (i = 0; i < 4; i++) {
        ROW_PORT->FIODIR |= (1 << row_pins[i]);
        ROW_PORT->FIOCLR = (1 << row_pins[i]);
    }
    for (i = 0; i < 4; i++) {
        pin = col_pins[i];
        pinmode_shift = (pin - 16) * 2;
        COL_PORT->FIODIR &= ~(1 << pin);
        LPC_PINCON->PINMODE4 &= ~(0x3 << pinmode_shift);
        LPC_PINCON->PINMODE4 |= (0x2 << pinmode_shift);
    }
}
int keypad_scan(void) {
    int row, col;

    for (row = 0; row < 4; row++) {
        ROW_PORT->FIOSET = (1 << row_pins[row]);
        delay_lcd(5);
        for (col = 0; col < 4; col++) {
            if ((COL_PORT->FIOPIN & (1 << col_pins[col])) != 0) {
                ROW_PORT->FIOCLR = (1 << row_pins[row]);
                return row * 4 + col;
            }
        }
        ROW_PORT->FIOCLR = (1 << row_pins[row]);
    }
    return -1;
}
void lcd_init(void) {
    unsigned int i;
    flag1 = 0;
    for (i = 0; i < sizeof(init_command) / sizeof(init_command[0]); i++) {
        temp1 = init_command[i];
        lcd_write();
    }
    flag1 = 1;
}
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
    volatile unsigned int r; 
    for (r = 0; r < count * 1000; r++) {
        __NOP();
    }
}
void lcd_clear(void) {
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();
    delay_lcd(2000);
    flag1 = 1;
}
void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address = (row == 0) ? 0x80 : 0xC0;
    address += col;
    flag1 = 0;
    temp1 = address;
    lcd_write();
    flag1 = 1;
}
void lcd_print(char *str) {
    flag1 = 1;
    while (*str) {
        temp1 = *str++;
        lcd_write();
    }
}
void lcd_send_char(char ch) {
    flag1 = 1;
    temp1 = ch;
    lcd_write();
}
int main(void) {
    SystemInit();
    SystemCoreClockUpdate();
    LPC_GPIO0->FIODIR |= (DT_CTRL | RS_CTRL | EN_CTRL);
    lcd_init();
    lcd_clear();
    lcd_print("Press SW2 to");
    lcd_set_cursor(1, 0);
    lcd_print("Roll Dice");
    LPC_PINCON->PINSEL4 &= ~(0x3 << 20);
    LPC_PINCON->PINSEL4 |= (0x1 << 20); 
    LPC_GPIO2->FIODIR &= ~(1 << 10);
    LPC_SC->EXTINT = 0x1;
    LPC_GPIOINT->IO2IntEnF |= (1 << 10);
    NVIC_EnableIRQ(EINT0_IRQn);
    keypad_init();
    while (1) {
        delay_lcd(100);
    }
}
