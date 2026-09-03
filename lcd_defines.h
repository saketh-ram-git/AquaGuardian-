#define LCD_DEFINES_H

#define LCD_DATA_MASK       0x000000FF

#define LCD_RS              (1 << 16)
#define LCD_EN              (1 << 17)

#define LCD_CLEAR           0x01
#define LCD_HOME            0x02

#define LCD_ENTRY_DEC_SHIFT 0x04
#define LCD_ENTRY_DEC       0x05
#define LCD_ENTRY_INC_SHIFT 0x06
#define LCD_ENTRY_INC       0x07

#define LCD_DISPLAY_OFF     0x08
#define LCD_DISPLAY_ON      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F

#define LCD_CURSOR_LEFT     0x10
#define LCD_CURSOR_RIGHT    0x14
#define LCD_DISPLAY_LEFT    0x18
#define LCD_DISPLAY_RIGHT   0x1C

#define LCD_8BIT_1LINE_5X8  0x30
#define LCD_8BIT_2LINE_5X8  0x38
#define LCD_8BIT_1LINE_5X10 0x34
#define LCD_8BIT_2LINE_5X10 0x3C

#define LCD_LINE1           0x80
#define LCD_LINE2           0xC0

