//rtc control functions will be here
#include<lpc21xx.h>
#include"rtc.h"
#include"types.h"
void init_rtc(void)
{
CCR = EDIT;                                                                                                                                                                                   
  PREINT = 456;
  PREFRAC = 25024;
  CCR = LOCK;
}
