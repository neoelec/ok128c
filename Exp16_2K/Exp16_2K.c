/* ========================================================================== */
/*                 Exp16_2.c : Integer Number Display Program                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>
#include <GLCD128.h>

static void GLCD_2d(uint8_t number)
{                                               /* display 2-digit decimal number */
    uint8_t i;

    i = number / 10;                            // 10^1
    if (i == 0)
        GLCD_English(' ');
    else
        GLCD_English(i + '0');

    i = number % 10;                            // 10^0
    GLCD_English(i + '0');
}

static void GLCD_3d(uint16_t number)
{                                               /* display 3-digit decimal number */
    uint16_t i;
    uint8_t flag;

    flag = 0;
    i = number / 100;                           // 10^2
    if (i == 0)
        GLCD_English(' ');
    else {
        GLCD_English(i + '0');
        flag = 1;
    }

    number = number % 100;                      // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0))
        GLCD_English(' ');
    else {
        GLCD_English(i + '0');
        flag = 1;
    }

    i = number % 10;                            // 10^0
    GLCD_English(i + '0');
}

static void GLCD_4d(uint16_t number)
{                                               /* display 4-digit decimal number */
    uint16_t i;
    uint8_t flag;

    flag = 0;
    i = number / 1000;                          // 10^3
    if (i == 0)
        GLCD_English(' ');
    else {
        GLCD_English(i + '0');
        flag = 1;
    }

    number = number % 1000;                     // 10^2
    i = number / 100;
    if ((i == 0) && (flag == 0))
        GLCD_English(' ');
    else {
        GLCD_English(i + '0');
        flag = 1;
    }

    number = number % 100;                      // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0))
        GLCD_English(' ');
    else {
        GLCD_English(i + '0');
        flag = 1;
    }

    i = number % 10;                            // 10^0
    GLCD_English(i + '0');
}

static void GLCD_2hex(uint8_t number)
{                                               /* display 2-digit hex number */
    uint8_t i;

    i = (number >> 4) & 0x0F;                   // 16^1
    if (i <= 9)
        GLCD_English(i + '0');
    else
        GLCD_English(i - 10 + 'A');

    i = number & 0x0F;                          // 16^0
    if (i <= 9)
        GLCD_English(i + '0');
    else
        GLCD_English(i - 10 + 'A');
}

static void GLCD_8bin(uint8_t number)
{                                               /* display 8-bit binary number */
    GLCD_English(((number >> 7) & 0x01) + '0'); // 2^7
    GLCD_English(((number >> 6) & 0x01) + '0'); // 2^6
    GLCD_English(((number >> 5) & 0x01) + '0'); // 2^5
    GLCD_English(((number >> 4) & 0x01) + '0'); // 2^4
    GLCD_English(((number >> 3) & 0x01) + '0'); // 2^3
    GLCD_English(((number >> 2) & 0x01) + '0'); // 2^2
    GLCD_English(((number >> 1) & 0x01) + '0'); // 2^1
    GLCD_English((number & 0x01) + '0');        // 2^0
}

int main(void)
{
    uint8_t i, j;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    GLCD_clear();                               // initialize GLCD screen
    cursor_flag = 0;                            // cursor off

    LCD_string(0x80, "Graphic LCD Test");       // display title
    LCD_string(0xC0, " Display Number ");

    while (1) {
        GLCD_string(0, 0, " ** ®ža?? ** ");    // display 8-bit integer
        GLCD_string(1, 0, "16»¥®= 0x00    ");
        GLCD_string(2, 0, "10»¥®= 000     ");
        GLCD_string(3, 0, " 2»¥®= 00000000");
        Beep();

        for (i = 1; i > 0; i++) {               // integer number from 1 to 255
            GLCD_xy(1, 10);                     // hexadecimal number
            GLCD_2hex(i);
            GLCD_xy(2, 8);                      // decimal number
            GLCD_3d((uint16_t) i);
            GLCD_xy(3, 8);                      // binary number
            GLCD_8bin(i);
            Delay_ms(500);
        }

        GLCD_string(0, 0, " **  e  ** ");  // display multiplication table(1)
        GLCD_string(1, 0, "                ");
        GLCD_string(2, 0, "   0 x 0 = 00   ");
        GLCD_string(3, 0, "                ");
        Beep();

        for (i = 2; i <= 9; i++)
            for (j = 1; j <= 9; j++) {
                GLCD_xy(2, 3);                  // display multiplicand
                GLCD_English(i + '0');
                GLCD_xy(2, 7);                  // display multiplier
                GLCD_English(j + '0');
                GLCD_xy(2, 11);                 // display multiplication
                GLCD_2d(i * j);
                Delay_ms(1000);
            }

        GLCD_string(0, 0, "** 2ža¡ ³­Q **");  // display multiplication table(2)
        GLCD_string(1, 0, "                ");
        GLCD_string(2, 0, " 00 x 00 = 0000 ");
        GLCD_string(3, 0, "                ");
        Beep();

        for (i = 10; i <= 90; i += 10)
            for (j = 10; j <= 90; j += 10) {
                GLCD_xy(2, 1);                  // display multiplicand
                GLCD_2d(i);
                GLCD_xy(2, 6);                  // display multiplier
                GLCD_2d(j);
                GLCD_xy(2, 11);                 // display multiplication
                GLCD_4d(i * j);
                Delay_ms(1000);
            }
    }

    return 0;
}
