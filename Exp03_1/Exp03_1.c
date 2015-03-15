/* ========================================================================== */
/*                    Exp03_1.c : Basic LCD Display Program                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>

int main(void)
{
    uint8_t i;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    while (1) {
        LCD_string(0x80, "  OK-128  V2.2  ");   // display logo
        LCD_string(0xC0, " ATmega128-16AI ");   // display message 1
        Beep();
        Delay_ms(2000);
        LCD_string(0xC0, "   2005/03/01   ");   // display message 2
        Beep();
        Delay_ms(2000);

        LCD_string(0x80, "0123456789ABCDEF0123456789ABCDEF");   // display long line
        LCD_string(0xC0, "Go shift left and right 16 times");
        Beep();
        Delay_ms(1000);

        for (i = 0; i < 16; i++) {              // shift left
            LCD_command(0x18);
            Delay_ms(300);
        }
        Delay_ms(1000);

        for (i = 0; i < 16; i++) {              // shift right
            LCD_command(0x1C);
            Delay_ms(300);
        }
        Delay_ms(1000);
    }

    return 0;
}
