#include"lcd.h"
#include"keypad.h"
#include"types.h"
extern u8 interrupt_flag;
extern s8 key;
extern u32 int_buff;
extern u32 alarm_period;
extern u32 target;
extern u32 remaining;
extern u32 glasses;
extern u32 alert_done;
extern u32 missed;
u32 key_int(void);
//menu function displays and performs menu operations
void MENU_FUN(void)
{
start:
    lcd_cmd(CLEAR_LCD);

    lcd_cmd(GOTO_LINE1_POS0);
    lcd_str("/:TIME *:TGT");

    lcd_cmd(GOTO_LINE2_POS0);
    lcd_str("-:FREQ +:EXIT");

    key = keyscan();

    switch(key)
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

            switch(key)
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

                    if(int_buff > 23)
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

                    if(int_buff > 59 )
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

                    if(int_buff > 7 || int_buff < 1)
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

            if(int_buff >=25)
            {
                lcd_cmd(CLEAR_LCD);
                lcd_cmd(GOTO_LINE1_POS0);
                lcd_str("   INVALID   ");
                delay_ms(200);
                goto target_input;
            }

            target = int_buff;
            glasses = 0;
            missed = 0;       /* Reset missed count on target update */
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

            delay_ms(200);

            int_buff = key_int();

            if(int_buff > 1440 || int_buff <= 0)
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
u32 key_int(void)
{
    lcd_cmd(GOTO_LINE2_POS0);
    int_buff=0;

    while((key=keyscan())!='+')
    {
        if(key=='*')
        {
            lcd_cmd(SHIFT_DSP_LEFT);
            lcd_write_8bit(' ');
            lcd_cmd(SHIFT_DSP_LEFT);
            int_buff/=10;
            delay_ms(100);
        }
        else
        {
            lcd_write_8bit(key);
            int_buff=(int_buff*10)+(key-48);
            delay_ms(100);
        }
    }

    lcd_cmd(CLEAR_LCD);
    return int_buff;
}
			           
 

