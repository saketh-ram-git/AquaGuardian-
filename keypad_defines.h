//keypad_defines.h
#include"types.h"
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23

u32 colscan(void);
u32 rowcheck(void);
u32 colcheck(void);
 u8 keyscan(void);
 void init_keypad(void);
 u32 key_int(void);


