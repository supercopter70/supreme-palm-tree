#include <stdio.h>
#include <string.h>

#define LCD_COMMAND     0xFE
#define LCD_CLEAR       0x01
#define LCD_LINE1       0x80
#define LCD_LINE2       0xC0

#define WriteByte(a) DRV_USART1_WriteByte(a)

void LCD_writeString(char *str);

void LCD_Clear();

void LCD_gotoLine1();

void LCD_gotoLine2();
