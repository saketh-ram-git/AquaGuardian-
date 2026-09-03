void delay_us(int tdly)
{
tdly*=12; 
while(tdly--);
}
void delay_ms(int tdly)
{
tdly*=12000;
while(tdly--);
}
void delay_s(int tdly)
{
tdly*=12000000;
while(tdly--);
}
