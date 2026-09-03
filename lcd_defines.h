   //lcd.h
#include <lpc21xx.h>
#include"defines.h"
#include "delay.h"
#include "types.h"

//PINS DEFINE
#define RS 14
#define EN 15
#define LCD_PINS 6


//LCD COMMANDS
#define CLEAR_LCD         0x01
#define RET_CUR_HOME      0x02
#define SHIFT_CUR_RIGHT   0x06
#define SHIFT_CUR_LEFT    0x07
#define DSP_OFF            0x08
#define DSP_ON_CUR_OFF    0x0C
#define DSP_ON_CUR_ON     0x0E
#define DSP_ON_CUR_BLK    0x0F
#define SHIFT_DSP_LEFT    0x10
#define SHIFT_DSP_RIGHT   0x14
#define MODE_8BIT_1LINE   0x30
#define MODE_4BIT_1LINE   0x20
#define MODE_8BIT_2LINE   0x38
#define MODE_4BIT_2LINE   0x28
#define GOTO_LINE1_POS0   0x80
#define GOTO_LINE2_POS0   0xC0
#define GOTO_LINE3_POS0   0x94
#define GOTO_LINE4_POS0   0xD4
#define GOTO_CGRAM_START  0x40



void init_lcd(void);
void lcd_write_8bit(u8 data);
void lcd_cmd(u8 cmd);
void lcd_str(s8 *ptr);
void lcd_write_int(u32 data);
void lcd_cgram_write(u8 *p);
