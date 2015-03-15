/* ========================================================================== */
/*                       Exp17_4.c : External Interrupt                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <OK128.h>

static uint16_t INT6_count, INT7_count;

static void LCD_3d(uint16_t number)
{                                               /* display 3-digit decimal number */
    uint16_t i;
    uint8_t flag;

    flag = 0;
    i = number / 100;                           // 10^2
    if (i == 0)
        LCD_data(' ');
    else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 100;                      // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0))
        LCD_data(' ');
    else {
        LCD_data(i + '0');
        flag = 1;
    }

    i = number % 10;                            // 10^0
    LCD_data(i + '0');
}

ISR(INT6_vect)
{                                               /* INT6 interrupt function */
    INT6_count++;                               // increment INT6 counter
    LCD_command(0x8D);                          // display INT6 counter
    LCD_3d(INT6_count);

    PORTB = _BV(PB4);                           // turn on LED1
    Delay_ms(500);
    PORTB = 0x00;                               // turn off LED1
}

ISR(INT7_vect)
{                                               /* INT7 interrupt function */
    INT7_count++;                               // increment INT7 counter
    LCD_command(0xCD);                          // display INT7 counter
    LCD_3d(INT7_count);

    PORTB = _BV(PB7);                           // turn on LED4
    Delay_ms(500);
    PORTB = 0x00;                               // turn off LED4
}

int main(void)
{
    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "SW1 : INT6 = 000");       // display title
    LCD_string(0xC0, "SW4 : INT7 = 000");
    Beep();

    DDRE |= _BV(DDE7) | _BV(DDE6);              // PORTE7-6 = output
    PORTE = _BV(PE6);                           // initialize PORTE7-6

    EICRB = _BV(ISC71) | _BV(ISC61);            // INT7 = falling, INT6 = rising
    EIMSK = _BV(INT7) | _BV(INT6);              // enable INT7, INT6
    EIFR = 0x00;
    sei();                                      // global interrupt enable

    PORTB = 0x00;                               // turn off all LEDs

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            PORTE &= ~_BV(PE6);                 // if SW1, generate INT6(rising edge)
            PORTE |= _BV(PE6);
            break;
        case (0xF0 & ~_BV(PF7)):
            PORTE |= _BV(PE7);                  // if SW4, generate INT7(falling edge)
            PORTE &= ~_BV(PE7);
            break;
        default:
            break;
        }
    }

    return 0;
}
