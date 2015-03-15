/* ========================================================================== */
/*              Exp03_4.c : Floating Point Number Display Program             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>

static void LCD_1d1(float number)
{                                               /* floating-point number x.x */
    uint16_t i, j;

    j = (uint16_t) (number * 10. + 0.5);
    i = j / 10;                                 // 10^0
    LCD_data(i + '0');
    LCD_data('.');
    i = j % 10;                                 // 10^-1
    LCD_data(i + '0');
}

static void LCD_2d2(float number)
{                                               /* floating-point number xx.xx */
    uint8_t i, j;

    j = (int32_t) (number * 100. + 0.5);
    i = j / 1000;                               // 10^1
    if (i == 0)
        LCD_data(' ');
    else
        LCD_data(i + '0');

    j = j % 1000;                               // 10^0
    i = j / 100;
    LCD_data(i + '0');
    LCD_data('.');

    j = j % 100;                                // 10^-1
    i = j / 10;
    LCD_data(i + '0');

    i = j % 10;                                 // 10^-2
    LCD_data(i + '0');
}

int main(void)
{
    uint8_t i, j;
    float x, y;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    while (1) {
        LCD_string(0x80, " FLOAT MULTIPLY ");   // display title
        LCD_string(0xC0, "0.0 x 0.0 =00.00");
        Beep();
        Delay_ms(1000);

        x = 0.0;                                // initial floating-point number

        for (i = 1; i <= 9; i++) {
            x += 1.1;
            y = 0.0;
            for (j = 1; j <= 9; j++) {
                y += 1.1;
                LCD_command(0xC0);
                LCD_1d1(x);                     // display multiplicand
                LCD_command(0xC6);
                LCD_1d1(y);                     // display multiplier
                LCD_command(0xCB);
                LCD_2d2(x * y);                 // display multiplication
                Delay_ms(1000);
            }
        }
    }

    return 0;
}
