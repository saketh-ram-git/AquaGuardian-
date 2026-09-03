#include <lpc21xx.h>

#include "delay.h"
#include "rtc.h"
#include "keypad.h"
#include "lcd.h"
#include "types.h"
#include "mini_project_defines.h"

#define EINT0_VIC_CHNO 14

void MENU_ISR(void) __irq;
void MENU_FUN(void);
void init_led_sws(void);
void alert_fun(void);
void update_status(void);
void startup_scroll(void);
void display_status(void);

u32 key_int(void);

u8 interrupt_flag = 0;
u8 alert_done = 0;

s8 key;
s8 key_buff[20];

volatile u32 target = 0;
volatile u32 glasses = 0;
volatile u32 remaining = 0;
volatile u32 missed = 0;

u32 dly;
u32 int_buff = 0;
u32 old_sec = 60;
u32 alarm_period = 2;


int main(void)
{
    u32 total_minutes = 0;

    /* Initialize peripherals */
    init_led_sws();
    init_lcd();
    init_keypad();
    init_rtc();

    startup_scroll();

    /* Configure P0.1 as EINT0 */
    PINSEL0 &= ~(3 << 2);
    PINSEL0 |= (3 << 2);

    /* Configure falling edge interrupt */
    EXTMODE |= (1 << 0);
    EXTPOLAR &= ~(1 << 0);

    /* Clear pending interrupt */
    EXTINT = (1 << 0);

    /* Configure VIC */
    VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO;
    VICVectAddr0 = (u32)MENU_ISR;
    VICIntEnable |= (1 << EINT0_VIC_CHNO);

    while (1)
    {
        if (target != 0)
        {
            if (glasses < target)
                remaining = target - glasses;
            else
                remaining = 0;
        }
        else
        {
            remaining = 0;
        }

        update_status();

        if (interrupt_flag)
        {
            MENU_FUN();
            old_sec = 60;
        }

        /* Convert current time to total minutes */
        total_minutes = (HOUR * 60) + MIN;

        if (target != 0 && remaining != 0 && alarm_period != 0)
        {
            if ((total_minutes % alarm_period == 0) &&
                SEC == 0 &&
                alert_done == 0)
            {
                alert_fun();
                alert_done = 1;
                old_sec = 60;
            }
        }

        if (SEC != 0)
        {
            alert_done = 0;
        }

        if (SEC != old_sec)
        {
            old_sec = SEC;
            display_status();
        }

        delay_ms(10);
    }
}


void display_status(void)
{
    lcd_cmd(GOTO_LINE1_POS0);
    DISP_TIME;

    lcd_cmd(0x80 + 12);
    lcd_str(" M");
    lcd_write_int(missed);

    lcd_cmd(GOTO_LINE2_POS0);
    lcd_write_8bit(0x00);

    lcd_str(" C");
    lcd_write_int(glasses);

    lcd_str(" T");
    lcd_write_int(target);

    lcd_str(" F");
    lcd_write_int(alarm_period);

    lcd_str(" R");
    lcd_write_int(remaining);
}


void startup_scroll(void)
{
    u32 i, j;
    u32 len;

    char msg[] = "AQUA GUARDIAN V25HE10G6";
    char scroll[60];

    len = 0;

    while (msg[len] != '\0')
        len++;

    for (i = 0; i < 16; i++)
        scroll[i] = ' ';

    for (i = 0; i < len; i++)
        scroll[i + 16] = msg[i];

    for (i = 0; i < 16; i++)
        scroll[len + 16 + i] = ' ';

    for (i = 0; i < len + 16; i++)
    {
        lcd_cmd(CLEAR_LCD);
        lcd_cmd(GOTO_LINE1_POS0);

        for (j = 0; j < 16; j++)
        {
            lcd_write_8bit(scroll[i + j]);
        }

        delay_ms(5);
    }

    lcd_cmd(CLEAR_LCD);
}


/* EINT0 interrupt handler */
void MENU_ISR(void) __irq
{
    interrupt_flag = 1;

    EXTINT = (1 << 0);
    VICVectAddr = 0;
}


void MENU_FUN(void)
{
start:

    lcd_cmd(CLEAR_LCD);

    lcd_cmd(GOTO_LINE1_POS0);
    lcd_str("/:TIME *:TGT");

    lcd_cmd(GOTO_LINE2_POS0);
    lcd_str("-:FREQ +:EXIT");

    key = keyscan();

    switch (key)
    {
        case '+':
            interrupt_flag = 0;
            return;


        case '/':

            lcd_cmd(CLEAR_LCD);
            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("TIME EDIT MODE");

            delay_ms(300);

time_menu:

            lcd_cmd(CLEAR_LCD);

            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("/:HOUR *:MIN");

            lcd_cmd(GOTO_LINE2_POS0);
            lcd_str("-:DOW +:EXIT");

            key = keyscan();

            switch (key)
            {
                case '+':
                    delay_ms(300);
                    goto start;


                case '/':

hour_input:

                    lcd_cmd(CLEAR_LCD);
                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("ENTER HOUR:");

                    lcd_cmd(GOTO_LINE2_POS0);
                    delay_ms(200);

                    int_buff = key_int();

                    if (int_buff > 23)
                    {
                        lcd_cmd(CLEAR_LCD);
                        lcd_cmd(GOTO_LINE1_POS0);
                        lcd_str("   INVALID   ");

                        delay_ms(200);
                        goto hour_input;
                    }

                    HOUR = int_buff;

                    lcd_cmd(CLEAR_LCD);
                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("HOUR UPDATED");

                    delay_ms(300);

                    goto time_menu;


                case '*':

min_input:

                    lcd_cmd(CLEAR_LCD);
                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("ENTER MIN:");

                    lcd_cmd(GOTO_LINE2_POS0);
                    delay_ms(200);

                    int_buff = key_int();

                    if (int_buff > 59)
                    {
                        lcd_cmd(CLEAR_LCD);
                        lcd_cmd(GOTO_LINE1_POS0);
                        lcd_str("   INVALID   ");

                        delay_ms(200);
                        goto min_input;
                    }

                    MIN = int_buff;

                    lcd_cmd(CLEAR_LCD);
                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("MIN UPDATED");

                    delay_ms(300);

                    goto time_menu;


                case '-':

dow_input:

                    lcd_cmd(CLEAR_LCD);
                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("ENTER DOW:");

                    lcd_cmd(GOTO_LINE2_POS0);
                    delay_ms(200);

                    int_buff = key_int();

                    if (int_buff > 7 || int_buff < 1)
                    {
                        lcd_cmd(CLEAR_LCD);
                        lcd_cmd(GOTO_LINE1_POS0);
                        lcd_str("   INVALID   ");

                        delay_ms(200);
                        goto dow_input;
                    }

                    DOW = int_buff;

                    lcd_cmd(CLEAR_LCD);
                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("WEEK UPDATED");

                    delay_ms(300);

                    goto time_menu;


                default:

                    lcd_cmd(CLEAR_LCD);

                    lcd_cmd(GOTO_LINE1_POS0);
                    lcd_str("  WRONG KEY   ");

                    lcd_cmd(GOTO_LINE2_POS0);
                    lcd_str("   PRESSED   ");

                    delay_ms(200);

                    goto time_menu;
            }


        case '*':

target_input:

            lcd_cmd(CLEAR_LCD);
            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("ENTER TARGET:");

            lcd_cmd(GOTO_LINE2_POS0);
            delay_ms(200);

            int_buff = key_int();

            if (int_buff > 24)
            {
                lcd_cmd(CLEAR_LCD);
                lcd_cmd(GOTO_LINE1_POS0);
                lcd_str("   INVALID   ");

                delay_ms(200);
                goto target_input;
            }

            /* Reset counters for the new target */
            target = int_buff;
            glasses = 0;
            missed = 0;
            remaining = target;
            alert_done = 0;

            lcd_cmd(CLEAR_LCD);
            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("TARGET UPDATED");

            delay_ms(200);

            goto start;


        case '-':

frequency_input:

            lcd_cmd(CLEAR_LCD);
            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("ENTER MINUTES:");

            lcd_cmd(GOTO_LINE2_POS0);
            delay_ms(200);

            int_buff = key_int();

            if (int_buff == 0 || int_buff > 1440)
            {
                lcd_cmd(CLEAR_LCD);
                lcd_cmd(GOTO_LINE1_POS0);
                lcd_str("   INVALID   ");

                delay_ms(200);
                goto frequency_input;
            }

            alarm_period = int_buff;

            lcd_cmd(CLEAR_LCD);
            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("FREQ UPDATED");

            delay_ms(200);

            goto start;


        default:

            lcd_cmd(CLEAR_LCD);

            lcd_cmd(GOTO_LINE1_POS0);
            lcd_str("  WRONG KEY   ");

            lcd_cmd(GOTO_LINE2_POS0);
            lcd_str("   PRESSED   ");

            delay_ms(200);

            goto start;
    }
}


/* Read multi-digit input from keypad */
u32 key_int(void)
{
    lcd_cmd(GOTO_LINE2_POS0);

    int_buff = 0;

    while ((key = keyscan()) != '+')
    {
        if (key == '*')
        {
            lcd_cmd(SHIFT_DSP_LEFT);
            lcd_write_8bit(' ');
            lcd_cmd(SHIFT_DSP_LEFT);

            int_buff /= 10;

            delay_ms(100);
        }
        else
        {
            lcd_write_8bit(key);

            int_buff = (int_buff * 10) + (key - '0');

            delay_ms(100);
        }
    }

    lcd_cmd(CLEAR_LCD);

    return int_buff;
}


/* Configure LEDs, buzzer and drink button */
void init_led_sws(void)
{
    IODIR0 |= (1 << RED_LED);
    IODIR0 |= (1 << GREEN_LED);
    IODIR0 |= (1 << YELLOW_LED);
    IODIR0 |= (1 << BUZZER);

    IODIR0 &= ~(1 << DRINK_BUTTON);

    IOCLR0 = (1 << RED_LED);
    IOCLR0 = (1 << GREEN_LED);
    IOCLR0 = (1 << YELLOW_LED);
    IOCLR0 = (1 << BUZZER);
}


/* Update hydration status LEDs */
void update_status(void)
{
    if (target == 0)
    {
        IOCLR0 = (1 << RED_LED);
        IOCLR0 = (1 << GREEN_LED);
    }
    else if (glasses >= target)
    {
        glasses = target;
        remaining = 0;

        IOCLR0 = (1 << RED_LED);
        IOSET0 = (1 << GREEN_LED);
    }
    else
    {
        IOSET0 = (1 << RED_LED);
        IOCLR0 = (1 << GREEN_LED);
    }
}


/* Water intake reminder */
void alert_fun(void)
{
    u32 count;
    u8 drink_pressed = 0;

    lcd_cmd(CLEAR_LCD);

    lcd_cmd(GOTO_LINE1_POS0);
    lcd_str("DRINK WATER!");

    lcd_cmd(GOTO_LINE2_POS0);
    lcd_write_8bit(0x00);

    lcd_str(" C");
    lcd_write_int(glasses);

    lcd_str(" T");
    lcd_write_int(target);

    lcd_str(" F");
    lcd_write_int(alarm_period);

    lcd_str(" R");
    lcd_write_int(remaining);

    IOCLR0 = (1 << RED_LED);
    IOSET0 = (1 << GREEN_LED);

    /* Alert for approximately one minute */
    for (count = 0; count < 60; count++)
    {
        IOSET0 = (1 << YELLOW_LED);
        IOSET0 = (1 << BUZZER);

        delay_ms(500);

        if (READBIT(IOPIN0, DRINK_BUTTON) == 1)
        {
            drink_pressed = 1;
            glasses++;

            if (glasses >= target)
            {
                glasses = target;
                remaining = 0;

                IOCLR0 = (1 << YELLOW_LED);
                IOCLR0 = (1 << BUZZER);
                IOCLR0 = (1 << RED_LED);
                IOSET0 = (1 << GREEN_LED);

                lcd_cmd(CLEAR_LCD);

                lcd_cmd(GOTO_LINE1_POS0);
                lcd_str("TARGET ACHIEVED");

                lcd_cmd(GOTO_LINE2_POS0);
                lcd_write_8bit(0x00);

                lcd_str(" C");
                lcd_write_int(glasses);

                lcd_str(" T");
                lcd_write_int(target);

                lcd_str(" F");
                lcd_write_int(alarm_period);

                lcd_str(" R");
                lcd_write_int(remaining);

                delay_ms(2000);

                lcd_cmd(CLEAR_LCD);

                break;
            }

            remaining = target - glasses;

            IOCLR0 = (1 << YELLOW_LED);
            IOCLR0 = (1 << BUZZER);

            IOSET0 = (1 << RED_LED);
            IOCLR0 = (1 << GREEN_LED);

            lcd_cmd(CLEAR_LCD);

            break;
        }

        IOCLR0 = (1 << YELLOW_LED);
        IOCLR0 = (1 << BUZZER);

        delay_ms(500);
    }

    /* Record missed reminder */
    if (!drink_pressed)
    {
        missed++;

        lcd_cmd(CLEAR_LCD);

        lcd_cmd(GOTO_LINE1_POS0);
        lcd_str(" GLASS MISSED! ");

        lcd_cmd(GOTO_LINE2_POS0);
        lcd_str("MISSED COUNT: ");

        lcd_write_int(missed);

        delay_ms(1500);
    }

    IOCLR0 = (1 << YELLOW_LED);
    IOCLR0 = (1 << BUZZER);

    update_status();

    lcd_cmd(CLEAR_LCD);
}

