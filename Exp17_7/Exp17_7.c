/* ========================================================================== */
/*                    Exp17_7.c : Change printf() Function                    */
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

static void USART0_initialize(void)
{                                               /* initialize USART0 */
    UBRR0H = 0;                                 // 19200 baud
    UBRR0L = 51;
    UCSR0A = 0x00;                              // asynchronous normal mode
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);           // Rx/Tx enable, 8 data
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);         // no parity, 1 stop, 8 data
}

static int USART0_putchar(char c, FILE * fp)
{                                               /* print a character to USART0 */
    if (c == '\n')                              // process CR(carriage return)
        USART0_putchar('\r', NULL);

    loop_until_bit_is_set(UCSR0A, UDRE0);       // Tx ready ?
    UDR0 = c;                                   // if yes, print
    return 0;
}

int main(void)
{
    uint8_t i = 1;
    double x = 0.001;
    FILE *fp;                                   // file pointer to be opened

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "SW1=LCD, SW4=232");       // display title
    LCD_string(0xC0, "                ");
    Beep();

    USART0_initialize();                        // initialize USART0

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            PORTB = _BV(PB4);                   // SW1 ?
            fp = fdevopen(LCD_putchar, NULL);
            LCD_command(0xC0);
            printf(" i=%03d  x=%5.3f ", i++, x);
            fclose(fp);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF7)):
            PORTB = _BV(PB7);                   // SW4 ?
            fp = fdevopen(USART0_putchar, NULL);
            printf(" i=%03d  x=%5.3f\n", i++, x);
            fclose(fp);
            x += 0.001;
            break;
        default:
            break;
        }
    }

    return 0;
}
