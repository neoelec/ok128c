/* ========================================================================== */
/*          Exp10_4.c : RS-232C Communication using USART1 Interrupt          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <OK128.h>

static uint8_t cursor;

ISR(USART1_RX_vect)
{                                               /* UART1 interrupt function */
    LCD_data(UDR1);                             // display a character
    cursor++;                                   // 16 character OK ?
    if (cursor == 16) {
        LCD_command(0xC0);                      // if yes, go home
        cursor = 0;
        Beep();
    }
}

static void TX1_char(char data)
{                                               /* transmit a character by USART1 */
    while ((UCSR1A & 0x20) == 0x00) ;           // data register empty ?
    UDR1 = data;
}

static void TX1_string(char *string)
{                                               /* transmit a string by USART1 */
    while (*string != '\0') {
        TX1_char(*string);
        string++;
    }
}

int main(void)
{
    uint8_t i;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    UBRR1H = 0;                                 // 19200 baud
    UBRR1L = 51;
    UCSR1A = 0x00;                              // asynchronous normal mode
    UCSR1B = _BV(RXCIE1) | _BV(RXEN1) | _BV(TXEN1); // interrupt enable, 8 data
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);         // no parity, 1 stop, 8 data
    i = UDR1;                                   // dummy read
    sei();                                      // global interrupt enable

    LCD_string(0x80, "RS-232C (USART1)");       // display title
    LCD_string(0xC0, "                ");
    Beep();

    LCD_command(0x0F);                          // cursor ON
    LCD_command(0xC0);                          // initial cursor position
    cursor = 0;

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            PORTB = _BV(PB4);                   // SW1 ?
            TX1_string("SW1 was pressed.");
            TX1_char(0x0D);
            TX1_char(0x0A);
            break;
        case (0xF0 & ~_BV(PF5)):
            PORTB = _BV(PB5);                   // SW2 ?
            TX1_string("SW2 was pressed.");
            TX1_char(0x0D);
            TX1_char(0x0A);
            break;
        case (0xF0 & ~_BV(PF6)):
            PORTB = _BV(PB6);                   // SW3 ?
            TX1_string("SW3 was pressed.");
            TX1_char(0x0D);
            TX1_char(0x0A);
            break;
        case (0xF0 & ~_BV(PF7)):
            PORTB = _BV(PB7);                   // SW4 ?
            TX1_string("SW4 was pressed.");
            TX1_char(0x0D);
            TX1_char(0x0A);
            break;
        default:
            break;
        }
    }

    return 0;
}
