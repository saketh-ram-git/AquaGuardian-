//RTC_DEFINES rtc.h
#include<lpc21xx.h>
//#define  PREINT 456
//#define PREFRAC 25024
#define EDIT 1<<1|1<<4;
#define LOCK 1<<0;
void init_rtc(void);
