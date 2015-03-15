/* ========================================================================== */
/*              Exp05_3.c : Variable-Frequency, Variable-Duty PWM             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>

static void LCD_4d(uint16_t number)
{                                               /* display 4-digit decimal number */
    uint16_t i;
    uint8_t flag;

    flag = 0;
    i = number / 1000;                          // 10^3
    if (i == 0)
        LCD_data(' ');
    else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 1000;                     // 10^2
    i = number / 100;
    if ((i == 0) && (flag == 0))
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

int main(void)
{
    uint16_t period, duty;

    MCU_initialize();                           // initialize MCU
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "Period =  1250*2");       // display title
    LCD_string(0xC0, "Duty   =   125*2");

    TCCR1A = _BV(COM1B1) | _BV(WGM10);          // Phase and Frequency Correct PWM mode(9)
    TCCR1B = _BV(WGM13) | _BV(CS11) | _BV(CS10);    // use OC1B
    TCCR1C = 0x00;
    OCR1AH = (1250 >> 8);                       // default PWM frequency(period)
    OCR1AL = 1250 & 0xFF;                       // f(PWM) = 16MHz/64/2/1250 = 100Hz
    period = 1250;
    OCR1BH = (125 >> 8);                        // default PWM duty ratio
    OCR1BL = 125 & 0xFF;                        // D(PWM) = 125/1250
    duty = 125;

    while (1) {
        switch (Key_input()) {                  // key input
        case (0xF0 & ~_BV(PF4)):
            if (duty != 0) {                    // if SW1, decrement duty ratio
                duty -= 125;
                OCR1BH = (duty >> 8);
                OCR1BL = duty & 0xFF;
                LCD_command(0xCA);
                LCD_4d(duty);
            }
            break;
        case (0xF0 & ~_BV(PF5)):
            if (duty != period) {               // if SW2, increment duty ratio
                duty += 125;
                OCR1BH = (duty >> 8);
                OCR1BL = duty & 0xFF;
                LCD_command(0xCA);
                LCD_4d(duty);
            }
            break;
        case (0xF0 & ~_BV(PF6)):
            if (period != 125) {                // if SW3, decrement period
                period -= 125;
                OCR1AH = (period >> 8);
                OCR1AL = period & 0xFF;
                LCD_command(0x8A);
                LCD_4d(period);
            }
            break;
        case (0xF0 & ~_BV(PF7)):
            if (period != 1250) {               // if SW4, increment period
                period += 125;
                OCR1AH = (period >> 8);
                OCR1AL = period & 0xFF;
                LCD_command(0x8A);
                LCD_4d(period);
            }
            break;
        default:
            break;
        }
    }

    return 0;
}
