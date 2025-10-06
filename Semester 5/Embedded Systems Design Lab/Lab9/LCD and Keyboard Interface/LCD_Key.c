#include "LPC17xx.h"

#define RS_CTRL (1 << 27)    // Pin 27
#define EN_CTRL (1 << 28)    // Pin 28
#define DT_CTRL 0x07800000   // Pins 23-26

unsigned long int temp1 = 0, temp2 = 0, i, j;
unsigned char flag1 = 0, flag2 = 0;
unsigned char msg1[] = {"Welcome"};
unsigned char msg2[] = {"to Manipal"};
void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);

unsigned long int init_command[] = {
    0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80
};

int main() {
    SystemInit();
    SystemCoreClockUpdate();

    LPC_GPIO0->FIODIR |= (DT_CTRL | RS_CTRL | EN_CTRL); // Configure pins as output

    flag1 = 0;
    for (i = 0; i < sizeof(init_command) / sizeof(init_command[0]); i++) {
        temp1 = init_command[i];
        lcd_write();
    }

    flag1 = 1;
    i = 0;
    while (msg1[i] != '\0') {  // Proper null-terminated string check
        temp1 = msg1[i];
        lcd_write();
        i++;
    }

		flag1 = 0;
		temp1 = 0xC0;
		lcd_write();
		
		flag1 = 1;
		i = 0;
		while(msg2 != '\0'){
				temp1 = msg2[i];
				lcd_write();
			  i++;
		}
		
    while (1);
}

void lcd_write(void) {
    // Set flag2 based on flag1 and temp1
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;

    // Send high nibble
    temp2 = (temp1 & 0xF0) << 19; // Shift bits 7-4 to GPIO pins 23-26 (DT_CTRL)
    port_write();

    if (!flag2) {
        // Send low nibble
        temp2 = (temp1 & 0x0F) << 23; // Shift bits 3-0 to GPIO pins 23-26
        port_write();
    }
}

void port_write(void) {
    // Clear the data pins first (pins 23-26)
    LPC_GPIO0->FIOCLR = DT_CTRL;

    // Set the data pins
    LPC_GPIO0->FIOSET = temp2 & DT_CTRL;

    // Control RS pin
    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = RS_CTRL;  // Command mode
    else
        LPC_GPIO0->FIOSET = RS_CTRL;  // Data mode

    // Pulse EN pin
    LPC_GPIO0->FIOSET = EN_CTRL;      // EN = 1
    delay_lcd(25);                    // Short delay (~1-2 ms)
    LPC_GPIO0->FIOCLR = EN_CTRL;      // EN = 0
    delay_lcd(5000);                  // Delay to let LCD process command/data
}

void delay_lcd(unsigned int count) {
    unsigned int r;
    for (r = 0; r < count * 1000; r++) {
        __NOP();  // Do nothing, simple delay
    }
}
