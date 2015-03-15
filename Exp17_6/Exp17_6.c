/* ========================================================================== */
/*              Exp17_6.c : printf() Function to Text LCD Module              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <stdio.h>

#include <OK128.h>

static int LCD_putchar(char c, FILE * fp)
{                                               /* print a character to LCD */
    if ((c < 0x20) | (c > 0x7E))                // check from 0x20 to 0x7E
        return 0;

    LCD_data(c);
    return 0;
}

int main(void)
{
    uint8_t i = 1;
    double x = 0.001;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "  use printf()  ");       // display title
    LCD_string(0xC0, "  to LCD module ");
    Beep();

    fdevopen(LCD_putchar, NULL);                // stdout and stderr device open

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            PORTB = _BV(PB4);                   // SW1 ?
            LCD_command(0x80);
            printf("SW1 was pressed.");
            LCD_command(0xC0);
            printf(" i=%03d  x=%5.3f ", i++, x);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF5)):
            PORTB = _BV(PB5);                   // SW2 ?
            LCD_command(0x80);
            printf("SW2 was pressed.");
            LCD_command(0xC0);
            printf(" i=%03d  x=%5.3f ", i++, x);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF6)):
            PORTB = _BV(PB6);                   // SW3 ?
            LCD_command(0x80);
            printf("SW3 was pressed.");
            LCD_command(0xC0);
            printf(" i=%03d  x=%5.3f ", i++, x);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF7)):
            PORTB = _BV(PB7);                   // SW4 ?
            LCD_command(0x80);
            printf("SW4 was pressed.");
            LCD_command(0xC0);
            printf(" i=%03d  x=%5.3f ", i++, x);
            x += 0.001;
            break;
        default:
            break;
        }
    }

    return 0;
}
