#include<lpc214x.h>

void delay(unsigned int a)
{
  unsigned int i,j;
	for(i=0;i<=1250;i++)
	for(j=0;j<a;j++);
}


void pll()
{
	PLL0CFG=0X41; //P=4(2 bits), M=2(5 bits)
	PLL0CON=0X01;  //enable PLL
	PLL0FEED=0XAA;  //feed sequence
	PLL0FEED=0X55;  //feed sequence
	while((PLL0STAT & 0X400)==0);      //wait for PLL to latch on target freq
	PLL0CON=0X03;   //enable & connect PLL
	VPBDIV=0X01;    //PCLK=CCLK=20MHz
	PLL0FEED=0XAA;    //feed sequence
	PLL0FEED=0X55;    //feed sequence
}

void UART0_init()
{
	PINSEL0=0x00000005;
	U0LCR=0x83;    //8 bits, no Parity, 1 Stop bit | DLAB=1
	U0DLM=0x00;
	U0DLL=0x82;   //DLL=130
	//U0FDR=0x52;  //MULVAL=5(7:4), DIVADDVAL=2(3:0)
	U0LCR=0x03;   //DLAB=0
}

void send_char(unsigned char a)
{
	while(!(U0LSR&0x20));   //wait until U0THR becomes empty
	U0THR=a;
}

void send_str(unsigned char *c)
{
	while(*c!='\0')
	{
		send_char(*c);
		c++;
  }
}

int main()
{
    pll();		
	  UART0_init();	
		send_str("Hello...");
	  send_str("Thanks For Visiting My Github Page");
	  while(1);
}
