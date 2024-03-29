/* ========================================================================== */
/*       Exp15_2.c : ASCII(English)-Only Display on Graphic LCD Module        */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include <OK128.h>

const unsigned char font[95][5] PROGMEM = {    /* 5x7 ASCII character font */
  { 0x00, 0x00, 0x00, 0x00, 0x00 },            // 0x20 space
  { 0x00, 0x00, 0x4f, 0x00, 0x00 },            // 0x21 !
  { 0x00, 0x07, 0x00, 0x07, 0x00 },            // 0x22 "
  { 0x14, 0x7f, 0x14, 0x7f, 0x14 },            // 0x23 #
  { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },            // 0x24 $
  { 0x23, 0x13, 0x08, 0x64, 0x62 },            // 0x25 %
  { 0x36, 0x49, 0x55, 0x22, 0x50 },            // 0x26 &
  { 0x00, 0x05, 0x03, 0x00, 0x00 },            // 0x27 '
  { 0x00, 0x1c, 0x22, 0x41, 0x00 },            // 0x28 (
  { 0x00, 0x41, 0x22, 0x1c, 0x00 },            // 0x29 )
  { 0x14, 0x08, 0x3e, 0x08, 0x14 },            // 0x2a *
  { 0x08, 0x08, 0x3e, 0x08, 0x08 },            // 0x2b +
  { 0x00, 0x50, 0x30, 0x00, 0x00 },            // 0x2c ,
  { 0x08, 0x08, 0x08, 0x08, 0x08 },            // 0x2d -
  { 0x00, 0x60, 0x60, 0x00, 0x00 },            // 0x2e .
  { 0x20, 0x10, 0x08, 0x04, 0x02 },            // 0x2f /
  { 0x3e, 0x51, 0x49, 0x45, 0x3e },            // 0x30 0
  { 0x00, 0x42, 0x7f, 0x40, 0x00 },            // 0x31 1
  { 0x42, 0x61, 0x51, 0x49, 0x46 },            // 0x32 2
  { 0x21, 0x41, 0x45, 0x4b, 0x31 },            // 0x33 3
  { 0x18, 0x14, 0x12, 0x7f, 0x10 },            // 0x34 4
  { 0x27, 0x45, 0x45, 0x45, 0x39 },            // 0x35 5
  { 0x3c, 0x4a, 0x49, 0x49, 0x30 },            // 0x36 6
  { 0x01, 0x71, 0x09, 0x05, 0x03 },            // 0x37 7
  { 0x36, 0x49, 0x49, 0x49, 0x36 },            // 0x38 8
  { 0x06, 0x49, 0x49, 0x29, 0x1e },            // 0x39 9
  { 0x00, 0x36, 0x36, 0x00, 0x00 },            // 0x3a :
  { 0x00, 0x56, 0x36, 0x00, 0x00 },            // 0x3b ;
  { 0x08, 0x14, 0x22, 0x41, 0x00 },            // 0x3c <
  { 0x14, 0x14, 0x14, 0x14, 0x14 },            // 0x3d =
  { 0x00, 0x41, 0x22, 0x14, 0x08 },            // 0x3e >
  { 0x02, 0x01, 0x51, 0x09, 0x06 },            // 0x3f ?
  { 0x32, 0x49, 0x79, 0x41, 0x3e },            // 0x40 @
  { 0x7e, 0x11, 0x11, 0x11, 0x7e },            // 0x41 A
  { 0x7f, 0x49, 0x49, 0x49, 0x36 },            // 0x42 B
  { 0x3e, 0x41, 0x41, 0x41, 0x22 },            // 0x43 C
  { 0x7f, 0x41, 0x41, 0x22, 0x1c },            // 0x44 D
  { 0x7f, 0x49, 0x49, 0x49, 0x41 },            // 0x45 E
  { 0x7f, 0x09, 0x09, 0x09, 0x01 },            // 0x46 F
  { 0x3e, 0x41, 0x49, 0x49, 0x7a },            // 0x47 G
  { 0x7f, 0x08, 0x08, 0x08, 0x7f },            // 0x48 H
  { 0x00, 0x41, 0x7f, 0x41, 0x00 },            // 0x49 I
  { 0x20, 0x40, 0x41, 0x3f, 0x01 },            // 0x4a J
  { 0x7f, 0x08, 0x14, 0x22, 0x41 },            // 0x4b K
  { 0x7f, 0x40, 0x40, 0x40, 0x40 },            // 0x4c L
  { 0x7f, 0x02, 0x0c, 0x02, 0x7f },            // 0x4d M
  { 0x7f, 0x04, 0x08, 0x10, 0x7f },            // 0x4e N
  { 0x3e, 0x41, 0x41, 0x41, 0x3e },            // 0x4f O
  { 0x7f, 0x09, 0x09, 0x09, 0x06 },            // 0x50 P
  { 0x3e, 0x41, 0x51, 0x21, 0x5e },            // 0x51 Q
  { 0x7f, 0x09, 0x19, 0x29, 0x46 },            // 0x52 R
  { 0x26, 0x49, 0x49, 0x49, 0x32 },            // 0x53 S
  { 0x01, 0x01, 0x7f, 0x01, 0x01 },            // 0x54 T
  { 0x3f, 0x40, 0x40, 0x40, 0x3f },            // 0x55 U
  { 0x1f, 0x20, 0x40, 0x20, 0x1f },            // 0x56 V
  { 0x3f, 0x40, 0x38, 0x40, 0x3f },            // 0x57 W
  { 0x63, 0x14, 0x08, 0x14, 0x63 },            // 0x58 X
  { 0x07, 0x08, 0x70, 0x08, 0x07 },            // 0x59 Y
  { 0x61, 0x51, 0x49, 0x45, 0x43 },            // 0x5a Z
  { 0x00, 0x7f, 0x41, 0x41, 0x00 },            // 0x5b [
  { 0x02, 0x04, 0x08, 0x10, 0x20 },            // 0x5c (\)
  { 0x00, 0x41, 0x41, 0x7f, 0x00 },            // 0x5d ]
  { 0x04, 0x02, 0x01, 0x02, 0x04 },            // 0x5e ^
  { 0x40, 0x40, 0x40, 0x40, 0x40 },            // 0x5f _
  { 0x00, 0x01, 0x02, 0x04, 0x00 },            // 0x60 `
  { 0x20, 0x54, 0x54, 0x54, 0x78 },            // 0x61 a
  { 0x7f, 0x48, 0x44, 0x44, 0x38 },            // 0x62 b
  { 0x38, 0x44, 0x44, 0x44, 0x20 },            // 0x63 c
  { 0x38, 0x44, 0x44, 0x48, 0x7f },            // 0x64 d
  { 0x38, 0x54, 0x54, 0x54, 0x18 },            // 0x65 e
  { 0x08, 0x7e, 0x09, 0x01, 0x02 },            // 0x66 f
  { 0x0c, 0x52, 0x52, 0x52, 0x3e },            // 0x67 g
  { 0x7f, 0x08, 0x04, 0x04, 0x78 },            // 0x68 h
  { 0x00, 0x04, 0x7d, 0x00, 0x00 },            // 0x69 i
  { 0x20, 0x40, 0x44, 0x3d, 0x00 },            // 0x6a j
  { 0x7f, 0x10, 0x28, 0x44, 0x00 },            // 0x6b k
  { 0x00, 0x41, 0x7f, 0x40, 0x00 },            // 0x6c l
  { 0x7c, 0x04, 0x18, 0x04, 0x7c },            // 0x6d m
  { 0x7c, 0x08, 0x04, 0x04, 0x78 },            // 0x6e n
  { 0x38, 0x44, 0x44, 0x44, 0x38 },            // 0x6f o
  { 0x7c, 0x14, 0x14, 0x14, 0x08 },            // 0x70 p
  { 0x08, 0x14, 0x14, 0x18, 0x7c },            // 0x71 q
  { 0x7c, 0x08, 0x04, 0x04, 0x08 },            // 0x72 r
  { 0x48, 0x54, 0x54, 0x54, 0x20 },            // 0x73 s
  { 0x04, 0x3f, 0x44, 0x40, 0x20 },            // 0x74 t
  { 0x3c, 0x40, 0x40, 0x20, 0x7c },            // 0x75 u
  { 0x1c, 0x20, 0x40, 0x20, 0x1c },            // 0x76 v
  { 0x3c, 0x40, 0x30, 0x40, 0x3c },            // 0x77 w
  { 0x44, 0x28, 0x10, 0x28, 0x44 },            // 0x78 x
  { 0x0c, 0x50, 0x50, 0x50, 0x3c },            // 0x79 y
  { 0x44, 0x64, 0x54, 0x4c, 0x44 },            // 0x7a z
  { 0x00, 0x08, 0x36, 0x41, 0x00 },            // 0x7b {
  { 0x00, 0x00, 0x77, 0x00, 0x00 },            // 0x7c |
  { 0x00, 0x41, 0x36, 0x08, 0x00 },            // 0x7d }
  { 0x08, 0x04, 0x08, 0x10, 0x08 }
};                                             // 0x7e ~

/* -------------------------------------------------------------------------- */
/*   Graphic LCD Module : Hyundai LCD,HG12605NY-LY,128x64 dot,LED backlight   */
/* -------------------------------------------------------------------------- */
/* LCD_DATABUS(0x2000) : D0-D7 = DB0-DB7 (7-14, data bus)		      */
/* LCD_CONTROL(0x2100) :   GND = R/-W    (5, read/write)		      */
/*                          D4 = D/-I    (4, data/instruction)		      */
/*                          D5 = E       (6, enable)			      */
/*                          D6 = CS1     (15, chip select 1)		      */
/*                          D7 = CS2     (16, chip select 2)		      */

uint8_t xcharacter, ycharacter;                // x character(0-7), y character(0-19)
uint8_t cursor_flag, xcursor, ycursor;         // x and y cursor position(0-7, 0-19)

void GLCD_command(uint8_t signal, uint8_t command)
{                                              /* write a command */
  LCD_CONTROL = signal & 0xC0;                 // D/-I = 0
  asm volatile (" PUSH  R0 ");                 // delay for 500 ns
  asm volatile (" POP   R0 ");
  asm volatile (" PUSH  R0 ");
  asm volatile (" POP   R0 ");
  LCD_DATABUS = command;                       // write command
  LCD_CONTROL = (signal & 0xC0) | 0x20;        // E = 1
  asm volatile (" PUSH  R0 ");                 // delay for 500 ns
  asm volatile (" POP   R0 ");
  asm volatile (" PUSH  R0 ");
  asm volatile (" POP   R0 ");
  LCD_CONTROL = signal & 0xC0;                 // E = 0
  asm volatile (" NOP      ");
  LCD_CONTROL = 0x00;                          // clear all control signals
  Delay_us(10);                                // wait for GLCD busy
}

void GLCD_data(uint8_t signal, uint8_t character)
{                                              /* write a data */
  LCD_CONTROL = (signal & 0xC0) | 0x10;        // D/-I = 1
  asm volatile (" PUSH  R0 ");                 // delay for 500 ns
  asm volatile (" POP   R0 ");
  asm volatile (" PUSH  R0 ");
  asm volatile (" POP   R0 ");
  LCD_DATABUS = character;                     // write data
  LCD_CONTROL = (signal & 0xC0) | 0x30;        // E = 1
  asm volatile (" PUSH  R0 ");                 // delay for 500 ns
  asm volatile (" POP   R0 ");
  asm volatile (" PUSH  R0 ");
  asm volatile (" POP   R0 ");
  LCD_CONTROL = (signal & 0xC0) | 0x10;        // E = 0
  asm volatile (" NOP      ");
  LCD_CONTROL = 0x00;                          // clear all control signals
  Delay_us(10);                                // wait GLCD busy
}

void GLCD_clear(void)
{                                              /* clear GLCD screen */
  uint8_t i, j, x;

  LCD_CONTROL = 0x00;                          // clear all control signals
  GLCD_command(0xC0, 0x3F);                    // CS1,CS2 display ON
  GLCD_command(0xC0, 0xC0);                    // CS1,CS2 display position

  x = 0xB8;
  for (i = 0; i <= 7; i++) {
    GLCD_command(0xC0, x);                     // X start addtess
    GLCD_command(0xC0, 0x40);                  // Y start address
    for (j = 0; j <= 63; j++)
      GLCD_data(0xC0, 0x00);                   // clear CS1 and CS2 screen
    x++;
  }
}

void GLCD_xy(uint8_t x, uint8_t y)
{                                              /* set character position */
  xcharacter = x;
  ycharacter = y;

  GLCD_command(0xC0, 0xB8 + xcharacter);       // X address

  if (ycharacter <= 9)                         // if y <= 9, CS1 Y address
    GLCD_command(0x40, 0x40 + ycharacter * 6 + 4);
  else                                         // if y >= 10, CS2 Y address
    GLCD_command(0x80, 0x40 + (ycharacter - 10) * 6);
}

void GLCD_character(uint8_t character)
{                                              /* display a character */
  uint8_t i, signal, font_data;

  GLCD_xy(xcharacter, ycharacter);
  if (ycharacter <= 9)                         // if y <= 9, CS1
    signal = 0x40;
  else                                         // if y >= 10, CS2
    signal = 0x80;
  for (i = 0; i <= 4; i++) {
    font_data = pgm_read_byte(&font[character - 0x20][i]);
    if ((cursor_flag == 1) && (xcharacter == xcursor) && (ycharacter == ycursor))
      GLCD_data(signal, font_data | 0x80);
    else
      GLCD_data(signal, font_data);
  }
  GLCD_data(signal, 0x00);                     // last byte 0x00

  ycharacter++;                                // go next character position
  if (ycharacter == 20) {
    ycharacter = 0;
    xcharacter++;
  }
}

void GLCD_string(uint8_t x, uint8_t y, char *string)
{                                              /* display a string */
  xcharacter = x;
  ycharacter = y;

  while (*string != '\0') {
    GLCD_character(*string);                   // display a charcater
    string++;
  }
}

int main(void)
{
  unsigned char i;

  MCU_initialize();                            // initialize MCU
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  GLCD_clear();                                // initialize GLCD screen
  cursor_flag = 0;                             // cursor off

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " ASCII(English) ");
  Beep();

  while (1) {
    GLCD_string(0, 0, "  OK-128 Kit  V2.2  "); // display screen 1
    GLCD_string(1, 0, "     03/01/2005     ");
    GLCD_string(2, 0, "                    ");
    GLCD_string(3, 0, "     Designed by    ");
    GLCD_string(4, 0, "   Duck-Yong Yoon.  ");
    GLCD_string(5, 0, "                    ");
    GLCD_string(6, 0, "      Made by       ");
    GLCD_string(7, 0, " Ohm Publishing Co. ");
    Delay_ms(5000);

    GLCD_string(0, 0, "     Hyundai LCD    "); // display screen 2
    GLCD_string(1, 0, "    HG12605NY-LY    ");
    GLCD_string(2, 0, "                    ");
    GLCD_string(3, 0, "    Yellow/Green    ");
    GLCD_string(4, 0, " LED Backlight Type ");
    GLCD_string(5, 0, "                    ");
    GLCD_string(6, 0, "128 x 64 Graphic LCD");
    GLCD_string(7, 0, " 6x8 Box, 5x7 ASCII ");
    Delay_ms(5000);

    GLCD_string(0, 0, "===================="); // display screen 3
    GLCD_string(1, 0, "  ASCII Characters  ");
    GLCD_string(2, 0, "====================");
    GLCD_string(7, 0, "                    ");

    GLCD_xy(3, 0);
    for (i = 0x20; i < 0x7F; i++)              // from 0x20 to 0x7E
      GLCD_character(i);
    Delay_ms(5000);
  }
}
