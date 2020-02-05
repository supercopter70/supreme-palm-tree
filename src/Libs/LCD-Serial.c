#include "LCD-Serial.h"

void LCD_writeString(char *str){
    int i = 0;
    while(i<strlen(str)){
        WriteByte(str[i]);
        i++;
    }
}

void LCD_Clear(){
    WriteByte(LCD_COMMAND);
    delay_ms(2);
    WriteByte(LCD_CLEAR);
    delay_ms(2);
}

void LCD_gotoLine1(){
    WriteByte(LCD_COMMAND);
    delay_ms(2);
    WriteByte(LCD_LINE1);
    delay_ms(2);
}

void LCD_gotoLine2(){
    WriteByte(LCD_COMMAND);
    delay_ms(2);
    WriteByte(LCD_LINE2);
    delay_ms(2);
}
