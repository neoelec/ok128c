/* ========================================================================== */
/*                   Exp17_5.c : printf() Function to USART0                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <stdio.h>

#include <OK128.h>

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

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "  use printf()  ");       // display title
    LCD_string(0xC0, "   to USART0    ");
    Beep();

    USART0_initialize();                        // initialize USART0
    fdevopen(USART0_putchar, NULL);             // stdout and stderr device open

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            PORTB = _BV(PB4);                   // SW1 ?
            printf("SW1 was pressed.  i=%3d  x=%5.3f\n", i++, x);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF5)):
            PORTB = _BV(PB5);                   // SW2 ?
            printf("SW2 was pressed.  i=%3d  x=%5.3f\n", i++, x);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF6)):
            PORTB = _BV(PB6);                   // SW3 ?
            printf("SW3 was pressed.  i=%3d  x=%5.3f\n", i++, x);
            x += 0.001;
            break;
        case (0xF0 & ~_BV(PF7)):
            PORTB = _BV(PB7);                   // SW4 ?
            printf("SW4 was pressed.  i=%3d  x=%5.3f\n", i++, x);
            x += 0.001;
            break;
        default:
            break;
        }
    }

    return 0;
}
