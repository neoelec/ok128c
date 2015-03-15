/* ========================================================================== */
/*                      Exp01_1a.c : Basic C Program (1)                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>

#include <OK128.h>

int main(void)
{
    MCU_initialize();                           // initialize MCU

    while (1) {
        PORTB = _BV(PB4) | _BV(PB6);            // LED1, 3 on
        Delay_ms(500);
        PORTB = _BV(PB5) | _BV(PB7);            // LED2, 4 on
        Delay_ms(500);
    }

    return 0;
}
