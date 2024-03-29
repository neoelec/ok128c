/* ========================================================================== */
/*                  Exp17_5.c : printf() Function to USART0                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <stdio.h>

#include <OK128.h>

void USART0_initialize(void)
{                                              /* initialize USART0 */
  UBRR0H = 0;                                  // 19200 baud
  UBRR0L = 51;
  UCSR0A = 0x00;                               // asynchronous normal mode
  UCSR0B = 0x18;                               // Rx/Tx enable, 8 data
  UCSR0C = 0x06;                               // no parity, 1 stop, 8 data
}

int USART0_putchar(char c, FILE * fp)
{                                              /* print a character to USART0 */
  if (c == '\n')                               // process CR(carriage return)
    USART0_putchar('\r', NULL);

  loop_until_bit_is_set(UCSR0A, UDRE0);        // Tx ready ?
  UDR0 = c;                                    // if yes, print
  return 0;
}

int main(void)
{
  unsigned char i = 1;
  double x = 0.001;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "  use printf()  ");        // display title
  LCD_string(0xC0, "   to USART0    ");
  Beep();

  USART0_initialize();                         // initialize USART0
  fdevopen(USART0_putchar, NULL);              // stdout and stderr device open

  while (1) {
    switch (Key_input()) {                     // key input
    case 0xE0:
      PORTB = 0x10;                            // SW1 ?
      printf("SW1 was pressed.  i=%3d  x=%5.3f\n", i++, x);
      x += 0.001;
      break;
    case 0xD0:
      PORTB = 0x20;                            // SW2 ?
      printf("SW2 was pressed.  i=%3d  x=%5.3f\n", i++, x);
      x += 0.001;
      break;
    case 0xB0:
      PORTB = 0x40;                            // SW3 ?
      printf("SW3 was pressed.  i=%3d  x=%5.3f\n", i++, x);
      x += 0.001;
      break;
    case 0x70:
      PORTB = 0x80;                            // SW4 ?
      printf("SW4 was pressed.  i=%3d  x=%5.3f\n", i++, x);
      x += 0.001;
      break;
    default:
      break;
    }
  }
}
