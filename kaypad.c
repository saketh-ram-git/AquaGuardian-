#include <lpc21xx.h>

#include "delay.h"
#include "types.h"
#include "lcd.h"
#include "keypad_defines.h"
#include "defines.h"


char keypad[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'#', '0', '=', 'D'}
};


void init_keypad(void)
{
    /* Configure row pins as outputs */
    WRITEBYTE(IODIR1, 0x0F, ROW0);

    /* Drive all rows low */
    IOCLR1 = 15 << ROW0;
}


u32 colscan(void)
{
    if (READNIBBLE(IOPIN1, COL0) != 15)
        return 0;
    else
        return 1;
}


u32 rowcheck(void)
{
    u32 rno;

    for (rno = 0; rno < 4; rno++)
    {
        /* Drive one row low at a time */
        WRITENIBBLE(IOPIN1, 15, ROW0);
        WRITENIBBLE(IOPIN1, ~(1 << rno), ROW0);

        if (colscan() == 0)
            break;
    }

    WRITENIBBLE(IOCLR1, 15, ROW0);

    return rno;
}


u32 colcheck(void)
{
    u32 cno;

    for (cno = 0; cno < 4; cno++)
    {
        if (READBIT(IOPIN1, COL0 + cno) == 0)
            break;
    }

    return cno;
}


u8 keyscan(void)
{
    u32 rno, cno;
    u8 key;

    init_keypad();

    /* Wait for a key press */
    while (colscan());

    rno = rowcheck();
    cno = colcheck();

    key = keypad[rno][cno];

    /* Restore all rows */
    WRITENIBBLE(IOPIN1, 15, ROW0);

    /* Simple debounce delay */
    delay_ms(1);

    return key;
}
