#include <LPC17xx.h>
#define RS (1<<27)
#define EN (1<<28)
#define DT (0xF<<23)
void lcd_pulse(void){
    LPC_GPIO0->FIOSET = EN;
    delay(1000);
    LPC_GPIO0->FIOCLR = EN;
    delay(3000);
}
void lcd_send_nibble(unsigned char nib){
    LPC_GPIO0->FIOCLR = DT;
    LPC_GPIO0->FIOSET = (nib << 23);
    lcd_pulse();
}
void lcd_command(unsigned char cmd){
    LPC_GPIO0->FIOCLR = RS;
    lcd_send_nibble((cmd >> 4) & 0x0F);
    lcd_send_nibble(cmd & 0x0F);
}
void lcd_data(unsigned char data){
    LPC_GPIO0->FIOSET = RS;
    lcd_send_nibble((data >> 4) & 0x0F);
    lcd_send_nibble(data & 0x0F);
}
void lcd_init(void){
    delay(20000);
    lcd_command(0x30);
    lcd_command(0x30);
    lcd_command(0x30);
    lcd_command(0x20);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
}
void lcd_print_number(int num){
    char buf[5];
    int i=0;
    if(num == 0) { lcd_data('0'); return; }
    while(num > 0){
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    while(i--)
        lcd_data(buf[i]);
}
void delay(unsigned int d){
    unsigned int i;
    for(i=0;i<d;i++);
}
int main(void){
    unsigned int adc4, adc5, diff;
    SystemInit();
    SystemCoreClockUpdate();
    LPC_GPIO0->FIODIR |= (RS | EN | DT);
    LPC_PINCON->PINSEL3 |= (3<<28);
    LPC_PINCON->PINSEL3 |= (3<<30);
    LPC_ADC->ADCR = (1<<21) |  (4<<8);
    lcd_init();
    lcd_command(0x80);
    lcd_data('D');
    lcd_data('i');
    lcd_data('f');
    lcd_data('f');
    lcd_data('=');
    while(1){
        LPC_ADC->ADCR |= (1<<24);
        while(!(LPC_ADC->ADDR4 & (1<<31)));
        adc4 = (LPC_ADC->ADDR4 >> 4) & 0xFFF;
        while(!(LPC_ADC->ADDR5 & (1<<31)));
        adc5 = (LPC_ADC->ADDR5 >> 4) & 0xFFF;
        diff = (adc4 > adc5) ? (adc4 - adc5) : (adc5 - adc4);
        lcd_command(0xC0);
        lcd_print_number(diff);
    }
}
