#include "LPC17xx.h"
#include <stdio.h> // For sprintf

// LCD pin definitions
#define RS_CTRL (1 << 27)    // P0.27
#define EN_CTRL (1 << 28)    // P0.28
#define DT_CTRL 0x07800000   // P0.23 to P0.26 (bits 23-26)

volatile uint8_t dice_number = 0;
volatile int seed = 1234; // RNG seed. Will be updated by random_seed().

// Keypad GPIO pins (assumed to be on P1 as per your example)
#define ROW_PORT LPC_GPIO1
#define COL_PORT LPC_GPIO1

// Pin numbers, NOT bit masks
const uint8_t row_pins[4] = {20, 21, 22, 23};  // P1.20 to P1.23 (Outputs)
const uint8_t col_pins[4] = {24, 25, 26, 27};  // P1.24 to P1.27 (Inputs)

// LCD commands for initialization in 4-bit mode
const unsigned long init_command[] = {
    0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80
};

// Global variables for LCD functions (to avoid C89 declaration issues in nested functions)
unsigned long temp1 = 0, temp2 = 0;
unsigned char flag1 = 0, flag2 = 0; // flag1: 0 for command, 1 for data. flag2: internal flag for 4-bit mode handling

// Function Prototypes
void delay_lcd(unsigned int count);
void lcd_write(void);
void port_write(void);
void lcd_init(void);
void lcd_clear(void);
void lcd_print(char *str);
void lcd_set_cursor(unsigned char row, unsigned char col);
void lcd_send_char(char ch); // Not used in this version but good to have

void EINT0_IRQHandler(void);
void random_seed(void);
int random_num(int max); // Changed to take 'max' directly
void keypad_init(void);
int keypad_scan(void);


int main(void) {
    // Variable declarations at the top of main for C89 compatibility
    // No specific local variables needed for the main loop,
    // other variables are global or within functions.

    SystemInit();
    SystemCoreClockUpdate();

    // Initialize LCD pins as output on P0
    LPC_GPIO0->FIODIR |= (DT_CTRL | RS_CTRL | EN_CTRL);

    // Initialize LCD
    lcd_init();
    lcd_clear();

    // Display welcome message
    lcd_print("Press SW2 to");
    lcd_set_cursor(1, 0);
    lcd_print("Roll Dice");

    // Setup External Interrupt on P2.10 (EINT0) for SW2
    // Ensure P2.10 is configured as an input with no pull-up/down if SW2 is externally pulled.
    // Assuming SW2 pulls P2.10 to GND when pressed, hence falling edge.
    LPC_PINCON->PINSEL4 &= ~(0x3 << 20);   // Clear bits for P2.10 (P2.10 func = 00 for GPIO)
    LPC_PINCON->PINSEL4 |= (0x1 << 20);    // Set P2.10 as EINT0 (Func = 01)

    LPC_GPIO2->FIODIR &= ~(1 << 10);       // Configure P2.10 as Input

    // You might want to configure pull-up/down for P2.10 if not done by external hardware
    // Example: Enable pull-up for P2.10 (PINMODE5, bits 20-21)
    // LPC_PINCON->PINMODE5 &= ~(0x3 << 20); // Clear bits (00 for pull-up)
    // Or, if button pulls to VCC and needs pull-down:
    // LPC_PINCON->PINMODE5 |= (0x2 << 20); // Set to 10 for pull-down


    LPC_SC->EXTINT = 0x1;                   // Clear EINT0 flag (write 1 to clear)
    LPC_GPIOINT->IO2IntEnF |= (1 << 10);   // Enable falling edge interrupt on P2.10

    NVIC_EnableIRQ(EINT0_IRQn);             // Enable EINT0 interrupt in NVIC

    // Initialize keypad GPIO pins
    keypad_init();

    while (1) {
        // Optional: Scan keypad in main loop if needed
        // int key = keypad_scan();
        // if (key != -1) {
        //     // Process key press, e.g., display it on LCD
        //     lcd_clear();
        //     lcd_print("Key:");
        //     lcd_set_cursor(1,0);
        //     char key_buffer[5];
        //     sprintf(key_buffer, "%d", key);
        //     lcd_print(key_buffer);
        // }
        // Add a small delay to prevent rapid polling
        delay_lcd(100);
    }
}

// RNG seeding function
void random_seed(void) {
    // Simple seed update based on a volatile counter.
    // In a real application, you'd use a timer, ADC noise, or true RNG source.
    // This provides a somewhat different seed on each button press.
    static volatile unsigned int counter = 0; // Static to retain value
    counter++;
    seed = (seed + counter * 3) % 65536; // Simple way to perturb the seed
}

// Simple Linear Congruential Generator for random number
// Returns a number from 1 to max (inclusive)
int random_num(int max) {
    seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF; // Standard LCG parameters
    return (seed % max) + 1; // For 1 to max inclusive (e.g., 1 to 6 for a die)
}

// External interrupt handler for SW2 (EINT0)
void EINT0_IRQHandler(void) {
    if (LPC_GPIOINT->IO2IntStatF & (1 << 10)) {
        // Debounce: A simple delay can be added here if needed, or in hardware
        delay_lcd(50); // Small debounce delay (e.g., 50ms)

        // Generate random number 1-6 for a dice
        random_seed();
        dice_number = random_num(6); // Max value is 6, result will be 1-6

        // Display dice number on LCD (clear and print)
        lcd_clear();
        lcd_print("Dice Roll:");
        lcd_set_cursor(1, 0);

        char buffer[3]; // Buffer for "6\0" or "1\0"
        sprintf(buffer, "%d", dice_number);
        lcd_print(buffer);

        // Clear interrupt flags
        LPC_GPIOINT->IO2IntClr = (1 << 10); // Clear GPIO interrupt
        LPC_SC->EXTINT |= 0x1;              // Clear External Interrupt flag (EINT0)
    }
}

// Initialize keypad pins: Rows as outputs (initially low), Columns as inputs with pull-down
void keypad_init(void) {
    int i;               // Declare loop variable at the top for C89 compatibility
    uint32_t pin;        // Declare at top
    uint32_t pinmode_shift; // Declare at top

    // Set rows as output, initialize low
    for (i = 0; i < 4; i++) {
        ROW_PORT->FIODIR |= (1 << row_pins[i]); // P1.20-P1.23 as Output
        ROW_PORT->FIOCLR = (1 << row_pins[i]);  // Initially LOW
    }

    // Set columns as input with pull-down resistors (P1.24-P1.27)
    // P1.16-P1.31 use PINSEL4 and PINMODE4
    // Each pin mode requires 2 bits.
    // For P1.24, it's (24-16)*2 = 8*2 = 16. So bits 17:16.
    // For P1.25, it's (25-16)*2 = 9*2 = 18. So bits 19:18.
    // etc.
    for (i = 0; i < 4; i++) {
        pin = col_pins[i]; // Get the actual pin number (24, 25, 26, 27)
        pinmode_shift = (pin - 16) * 2; // Calculate shift for PINMODE4

        COL_PORT->FIODIR &= ~(1 << pin); // Configure P1.x as Input

        // Configure PINMODE for pull-down (0b10) for P1.24-P1.27
        // PINMODE4 covers P1.16 to P1.31
        LPC_PINCON->PINMODE4 &= ~(0x3 << pinmode_shift); // Clear existing mode bits
        LPC_PINCON->PINMODE4 |= (0x2 << pinmode_shift);  // Set to 10 for pull-down
    }
}

// Scan keypad: Return pressed key number (0-15) or -1 if none pressed
int keypad_scan(void) {
    int row, col; // Declare loop variables at the top for C89 compatibility

    for (row = 0; row < 4; row++) {
        // Drive one row high
        ROW_PORT->FIOSET = (1 << row_pins[row]);

        // Small delay for signal to settle
        delay_lcd(5);

        // Read columns
        for (col = 0; col < 4; col++) {
            if ((COL_PORT->FIOPIN & (1 << col_pins[col])) != 0) {
                // Key at (row,col) pressed
                // Drive row low before returning
                ROW_PORT->FIOCLR = (1 << row_pins[row]);

                // Return a unique key code (0 to 15 for 16 keys)
                return row * 4 + col;
            }
        }
        // Drive row low before next iteration
        ROW_PORT->FIOCLR = (1 << row_pins[row]);
    }
    return -1; // No key pressed
}

// LCD initialization in 4-bit mode
void lcd_init(void) {
    unsigned int i; // Declare loop variable at the top for C89 compatibility

    flag1 = 0;  // Command mode
    for (i = 0; i < sizeof(init_command) / sizeof(init_command[0]); i++) {
        temp1 = init_command[i];
        lcd_write();
    }
    flag1 = 1;  // Data mode
}

// Write one command or data to LCD
void lcd_write(void) {
    // Determine if it's an initial 4-bit command (0x30, 0x20) where only high nibble is sent
    // flag2 is 1 for initial 4-bit commands, 0 otherwise (meaning both nibbles are sent)
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;

    // Send high nibble (bits 7-4 of temp1)
    // Shifted to pins 23-26 (DT_CTRL starts at bit 23)
    temp2 = (temp1 & 0xF0) << 19; // Bits 7-4 (0xF0) shift to P0.26-P0.23
    port_write();

    if (!flag2) { // If not one of the special initial 4-bit commands
        // Send low nibble (bits 3-0 of temp1)
        // Shifted to pins 23-26
        temp2 = (temp1 & 0x0F) << 23; // Bits 3-0 (0x0F) shift to P0.26-P0.23
        port_write();
    }
}

// Write to GPIO port for LCD data and control pins
void port_write(void) {
    // Clear data pins first (P0.23-P0.26)
    LPC_GPIO0->FIOCLR = DT_CTRL;

    // Set data pins with the calculated temp2 (which has the nibble in position)
    LPC_GPIO0->FIOSET = temp2 & DT_CTRL;

    // Control RS pin (P0.27)
    if (flag1 == 0) // Command mode
        LPC_GPIO0->FIOCLR = RS_CTRL;
    else            // Data mode
        LPC_GPIO0->FIOSET = RS_CTRL;

    // Pulse EN pin (P0.28)
    LPC_GPIO0->FIOSET = EN_CTRL;  // EN = 1
    delay_lcd(25);                // Short delay (~1-2 ms) for EN pulse width
    LPC_GPIO0->FIOCLR = EN_CTRL;  // EN = 0
    delay_lcd(5000);              // Longer delay for LCD to process command/data
}

// Delay function (~1 ms per count, depends on clock frequency and __NOP() cycles)
void delay_lcd(unsigned int count) {
    volatile unsigned int r; // Declare loop variable at the top for C89 compatibility
    for (r = 0; r < count * 1000; r++) {
        __NOP();  // Do nothing, simple delay
    }
}

// Clear LCD screen
void lcd_clear(void) {
    flag1 = 0;        // Command mode
    temp1 = 0x01;     // Clear display command
    lcd_write();
    delay_lcd(2000);  // Longer delay for clear command (around 2ms)
    flag1 = 1;        // Return to Data mode
}

// Set cursor position (row:0 or 1, col:0-15)
void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address = (row == 0) ? 0x80 : 0xC0; // 0x80 for row 0, 0xC0 for row 1
    address += col;
    flag1 = 0;   // Command mode
    temp1 = address;
    lcd_write();
    flag1 = 1;   // Return to Data mode
}

// Print string to LCD (data mode)
void lcd_print(char *str) {
    flag1 = 1;  // Ensure Data mode
    while (*str) { // Loop until null terminator
        temp1 = *str++; // Get character and advance pointer
        lcd_write();
    }
}

// Function to send a single character (not explicitly used for dice, but useful)
void lcd_send_char(char ch) {
    flag1 = 1; // Data mode
    temp1 = ch;
    lcd_write();
}