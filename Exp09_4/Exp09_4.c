/* ========================================================================== */
/*               Exp09_4.c : Variable D/A Frequency by Key Input              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <OK128.h>

static uint8_t i;

static const uint8_t sin_table[] PROGMEM = {    // sine wave data table
    0x80, 0x88, 0x90, 0x98, 0xA0, 0xA7, 0xAF, 0xB6, 0xBD, 0xC4,
    0xCB, 0xD1, 0xD7, 0xDD, 0xE2, 0xE7, 0xEB, 0xEF, 0xF3, 0xF6,
    0xF9, 0xFB, 0xFD, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFD, 0xFB,
    0xF9, 0xF6, 0xF3, 0xEF, 0xEB, 0xE7, 0xE2, 0xDD, 0xD7, 0xD1,
    0xCB, 0xC4, 0xBD, 0xB6, 0xAF, 0xA7, 0xA0, 0x98, 0x90, 0x88,
    0x80, 0x78, 0x70, 0x68, 0x60, 0x59, 0x51, 0x4A, 0x43, 0x3C,
    0x35, 0x2F, 0x29, 0x23, 0x1E, 0x19, 0x15, 0x11, 0x0D, 0x0A,
    0x07, 0x05, 0x03, 0x02, 0x01, 0x01, 0x01, 0x02, 0x03, 0x05,
    0x07, 0x0A, 0x0D, 0x11, 0x15, 0x19, 0x1E, 0x23, 0x29, 0x2F,
    0x35, 0x3C, 0x43, 0x4A, 0x51, 0x59, 0x60, 0x68, 0x70, 0x78
};

ISR(TIMER1_COMPA_vect)
{                                               /* OC1A interrupt function */
    PORTB = pgm_read_byte(&sin_table[i]);       // output data to D/A
    i++;
    if (i == 100)
        i = 0;
}

static void LCD_3digit(uint8_t number)
{                                               /* display 3-digit decimal number */
    uint8_t i;

    LCD_data(number / 100 + '0');               // 10^2
    i = number % 100;
    LCD_data(i / 10 + '0');                     // 10^1
    LCD_data(i % 10 + '0');                     // 10^0
}

void Set_timer1(uint8_t number)
{                                               /* set Timer1 OCR1A */
    OCR1AH = 0x00;                              // set OCR1A
    OCR1AL = number - 1;
    LCD_command(0xCA);                          // display div_ratio
    LCD_3digit(number);
}

int main(void)
{
    uint8_t div_ratio;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "   D/A Output   ");       // display title
    LCD_string(0xC0, "16MHz/800/200 Hz");
    Beep();

    TCCR1A = 0x00;                              // CTC mode(4), don't output OC1A
    TCCR1B = _BV(WGM12) | _BV(CS11);            // 16MHz/8/(1+199) = 10kHz
    TCCR1C = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 199;
    TCNT1H = 0x00;                              // clear Timer/Counter1
    TCNT1L = 0x00;

    TIMSK = _BV(OCIE1A);                        // enable OC1A interrupt
    TIFR = 0x00;                                // clear all interrupt flags
    sei();                                      // global interrupt enable

    i = 0;
    div_ratio = 200;                            // initial division ratio

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            if (div_ratio != 100)               // if SW1, decrement by 1
                div_ratio--;
            Set_timer1(div_ratio);
            break;
        case (0xF0 & ~_BV(PF5)):
            if (div_ratio != 240)               // if SW2, increment by 1
                div_ratio++;
            Set_timer1(div_ratio);
            break;
        case (0xF0 & ~_BV(PF6)):
            div_ratio -= 10;                    // if SW3, decrement by 10
            if (div_ratio < 100)
                div_ratio = 100;
            Set_timer1(div_ratio);
            break;
        case (0xF0 & ~_BV(PF7)):
            div_ratio += 10;                    // if SW4, increment by 10
            if (div_ratio > 240)
                div_ratio = 240;
            Set_timer1(div_ratio);
            break;
        default:
            break;
        }
    }

    return 0;
}
