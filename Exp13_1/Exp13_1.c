/* ========================================================================== */
/*            Exp13_1.c : Display Same Characters on 7-Segment LED            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>

static uint8_t Bin2LED(uint8_t number)
{                                               /* convert binary to LED pattern */
    if (number == 0)
        return 0xFC;
    else if (number == 1)
        return 0x60;
    else if (number == 2)
        return 0xDA;
    else if (number == 3)
        return 0xF2;
    else if (number == 4)
        return 0x66;
    else if (number == 5)
        return 0xB6;
    else if (number == 6)
        return 0xBE;
    else if (number == 7)
        return 0xE4;
    else if (number == 8)
        return 0xFE;
    else if (number == 9)
        return 0xF6;
    else if (number == 10)
        return 0xEE;
    else if (number == 11)
        return 0x3E;
    else if (number == 12)
        return 0x9C;
    else if (number == 13)
        return 0x7A;
    else if (number == 14)
        return 0x9E;
    else if (number == 15)
        return 0x8E;
    else if (number == '-')
        return 0x02;
    else if (number == '.')
        return 0x01;
    else
        return 0x00;
}

int main(void)
{
    uint8_t i, j;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, " 7-SEGMENT LED  ");       // display title
    LCD_string(0xC0, "                ");

    while (1) {
        Beep();
        DIG_SELECT = 0xFF;                      // select all digits

        for (i = 0; i <= 0x0F; i++) {           // display from 0 to F
            LCD_DATABUS = Bin2LED(i);
            Delay_ms(1000);
        }
        LCD_DATABUS = Bin2LED('-');             // display "-"
        Delay_ms(1000);
        LCD_DATABUS = Bin2LED('.');             // display "."
        Delay_ms(1000);

        j = 0xFF;
        for (i = 0; i < 3; i++) {               // display random pattern
            DIG_SELECT = j;
            LCD_DATABUS = 0x04;
            Delay_ms(100);
            LCD_DATABUS = 0x80;
            Delay_ms(100);
            LCD_DATABUS = 0x40;
            Delay_ms(100);
            LCD_DATABUS = 0x02;
            Delay_ms(100);
            LCD_DATABUS = 0x08;
            Delay_ms(100);
            LCD_DATABUS = 0x10;
            Delay_ms(100);
            LCD_DATABUS = 0x20;
            Delay_ms(100);
            LCD_DATABUS = 0x02;
            Delay_ms(100);
            if (i == 0)
                j = 0xAA;
            else if (i == 1)
                j = 0x55;
        }
    }

    return 0;
}
