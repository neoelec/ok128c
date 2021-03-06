/* ========================================================================== */
/*            Exp08_5.c : A/D Converter ADC3 vs ADC2 Bipolar Input            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <math.h>

#include <OK128.h>

static void LCD_s1d2(float number)
{                                               /* floating-point number x.xx */
    uint16_t i, j;

    if (number >= 0.)
        LCD_data('+');                          // sign +/-
    else
        LCD_data('-');

    j = (int)(fabs(number) * 100. + 0.5);
    i = j / 100;                                // 10^0
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
    uint8_t i;
    int16_t sum;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "  ADC3 vs ADC2  ");       // display title
    LCD_string(0xC0, "    +0.00[V]    ");
    Beep();

    ADMUX = _BV(ADLAR) | _BV(MUX4) |
            _BV(MUX3) | _BV(MUX1) | _BV(MUX0);  // diffrential ADC3 vs ADC2 with gain 1
                                                //   (use left adjust and AREF)
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);  // ADC enable, 125kHz
    Delay_us(200);

    while (1) {
        sum = 0;
        for (i = 0; i < 16; i++) {              // read ADC by 16 times
            ADCSRA &= ~_BV(ADIF);               // clear ADIF
            ADCSRA |= _BV(ADSC);                // start conversion
            loop_until_bit_is_set(ADCSRA, ADIF);
            sum += (ADCL + ADCH * 256) / 64;    // add A/D result 16 times
            Delay_ms(1);
        }

        sum = sum / 16;                         // divide sum by 16

        LCD_command(0xC4);                      // display in voltage(+/-X.XX)
        LCD_s1d2(sum * 5. / 512.);              // Volt = sum*50/512

        Delay_ms(200);                          // delay 200 ms
    }

    return 0;
}
