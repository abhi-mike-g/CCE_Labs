#include <LPC17xx.h>
#define PWM_PINSEL (1 << 2) 
#define ROW0_MASK  (0xF << 0)
void init_pwm(void);
void set_duty_cycle(unsigned int duty);
int main(void)
{
    uint32_t key;
    LPC_PINCON->PINSEL2 &= ~(0x3F);
    LPC_GPIO1->FIODIR  &= ~ROW0_MASK;
    init_pwm();
    while (1){
        key = LPC_GPIO1->FIOPIN & ROW0_MASK;
        switch (key){
            case 0x00000001:
                set_duty_cycle(10);
                break;
            case 0x00000002:
                set_duty_cycle(25);
                break;
            case 0x00000004:
                set_duty_cycle(50);
                break;
            case 0x00000008:
                set_duty_cycle(75);
                break;
            default:
                break;
        }}}
void init_pwm(void)
{
    LPC_PINCON->PINSEL4 &= ~(3 << 2);
    LPC_PINCON->PINSEL4 |=  (1 << 2);
    LPC_SC->PCONP |= (1 << 6);
    LPC_PWM1->PR = 0x00;
    LPC_PWM1->MR0 = 1000;
    LPC_PWM1->MR2 = 100;
    LPC_PWM1->LER = (1 << 0) | (1 << 2);
    LPC_PWM1->PCR = (1 << 10);
    LPC_PWM1->MCR = (1 << 1);
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);
}
void set_duty_cycle(unsigned int duty)
{
    LPC_PWM1->MR2 = (duty * 1000) / 100;
    LPC_PWM1->LER |= (1 << 2);
}
