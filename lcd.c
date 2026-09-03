#include<lpc21xx.h>
#include"delay.h"
#include"lcd.h"
#include"defines.h"
#include"types.h"
#include<stdio.h>
//#define WRITEBYTE(WORD,BYTE,STARTBIT_POSN)   WORD = (((WORD & ~(0XFF<<STARTBIT_POSN)) | BYTE<<STARTBIT_POSN));
u8 glass[8] = { 0x1f,0x11,0x0a,0x04,0x04,0x04,0x0e,0x1f};
void init_lcd(void)
{

  IODIR0 |= 0XFF<<LCD_PINS|1<<RS|1<<EN;
         lcd_cmd(0x38);
        lcd_cmd(DSP_ON_CUR_OFF);
        lcd_cmd(0x01);
        lcd_cmd(0x80);
	       lcd_cgram_write(glass);
}
void lcd_cmd(u8 cmd)
{
  IOCLR0 = 1<<RS;
  WRITEBYTE(IOPIN0,cmd,LCD_PINS);
  IOSET0 = 1<<EN;
  delay_ms(1);
  IOCLR0 = 1<<EN;
  delay_ms(2);

}
void lcd_write_8bit(u8 data)
{
         IOSET0 = 1<<RS;
  WRITEBYTE(IOPIN0,data,LCD_PINS);
  IOSET0 = 1<<EN;
  delay_ms(1);
  IOCLR0 = 1<<EN;
  delay_ms(2);
  //lcd_cmd(0x06);

}
void lcd_str(s8 *ptr)
{
   while(*ptr != '\0')
   {
       lcd_write_8bit(*ptr);
           ptr++;
   }
}
void lcd_write_int(u32 data)
{       s8 arr[15];
    sprintf(arr,"%u",data);
        lcd_str(arr);
}
void lcd_cgram_write(u8 *p)
{
	u8 i;
	lcd_cmd(0x40);
	for(i=0;i<8;i++)
	lcd_write_8bit(p[i]);
}



