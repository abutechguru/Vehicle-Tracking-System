#define F_CPU 12000000UL //define mcu clock speed
#include <avr/io.h> //include AVR Header file
#include <inttypes.h> // include inttype header file
#include <util/delay.h> //include delay header file
#include"lcd_16.h" //include lcd header file
#include"lcd_16.c" //include lcd c file
int i=0;
void wait(float x) //wait function
{
for(i=0;i<(int)(1302*x);i++)
_delay_loop_1(0);

}

void USARTInit(uint16_t ubrr_value) //usart initialization function
{
UBRRL = ubrr_value; //Baud rate selection
UBRRH = (ubrr_value>>8);


UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);

UCSRB=(1<<RXEN)|(1<<TXEN);

}
unsigned char USARTReadChar() //USART Recieving Function
{
while(!(UCSRA & (1<<RXC)));
return UDR;
}
void usart_putstr( const unsigned char *str ) //String Function
{
for( ;*str != 0x00; )
{
USARTWriteChar( *str++ );
}

}

void USARTWriteChar(char data) //USART Transmiting function
{
while(!(UCSRA & (1<<UDRE)));
UDR=data;
}
void USART_StringTransmit(unsigned char s[]) //function for string transmit
{
int i=0;
while(s[i]!='\0')
{
USARTWriteChar(s[i]);
i++;
}

}
char buffer[16];

void main() //main function
{
unsigned char data;

DDRA=0x00; //Declare Port A as a input port

char sentence[100],lattitude[11],longitude[11],sentences[5],stored_d[9]="position";

char *str;

USARTInit(77); //initalize Baudrate value

lcd_init(LCD_DISP_ON); //LCD Initialize

int c=0,r=0,i=0,j=0,k=0,a=0,l=0;

while(1) //infinite loop
{
while(1)
{
data=USARTReadChar(); // this loop keeps on repeating untill the recived
char.
if(data=='+') // is not '+' character.
{
for(i=0;i<=10;i++)
data=USARTReadChar(); //passing 10 characters after character '+' is recived
break; // break inner while loop
}
}

USARTWriteChar('A');

wait(1);
USARTWriteChar('T'); //sending AT followed by enter (carrige return) to
GSM Modem
wait(1);
USARTWriteChar('\n\r'); //carrige return

wait(1);
USARTWriteChar('A');

USARTWriteChar('T'); // sending AT+CMGF=1, an AT command to set

msg. format

USARTWriteChar('+');
USARTWriteChar('C');
USARTWriteChar('M');
USARTWriteChar('G');

USARTWriteChar('F');
USARTWriteChar('=');
USARTWriteChar('1');
USARTWriteChar('\n\r');

wait(1);

USARTWriteChar('A');
USARTWriteChar('T');
USARTWriteChar('+');

USARTWriteChar('C'); //sending AT command, AT+CMGR=1, to read

msg. from inbox at location 1
USARTWriteChar('M');
USARTWriteChar('G');

USARTWriteChar('R');
USARTWriteChar('=');
USARTWriteChar('1');
USARTWriteChar('\n\r');

lcd_gotoxy(0,0);

for(i=0;i<=75;i++)
data=USARTReadChar(); //Reading 76 characters from the modem but not
using them


for(k=0;k<=8;k++) // Reading 5 characters from the modem & storing

them in an array
sentences[k]=USARTReadChar(); //main msg text is stored in this array
for(k=0;k<8;k++)
{
if(sentences[k]==stored_d[k])
{ // here al five characters of the recived msg.
data=USARTReadChar();
if(data=='$')
if(USARTReadChar()=='G')

if(USARTReadChar()=='P')
if(USARTReadChar()=='G')
if(USARTReadChar()=='G')
if(USARTReadChar()=='A')
{
for(l=1;l<=12;l++)
data=USARTReadChar();
for(a=0;a<=8;a++,l++)

lattitude[a]=USARTReadChar();

lattitude[a]='\0';
for(a=0;a<3;a++)
data=USARTReadChar();
for(a=0;a<=9;a++,l++)

longitude[a]=USARTReadChar();

longitude[a]='\0';

lcd_gotoxy(0,0);
sprintf(buffer,"Latt:%s",lattitude);
lcd_puts(buffer);
lcd_gotoxy(0,1);
sprintf(buffer,"Long:%s",longitude);
lcd_puts(buffer);
}

}
lcd_clrscr();
wait(3);
USARTWriteChar('A'); // Then print AC ON on LCD & sending the AT command
USARTWriteChar('T'); // to modem to send a msg. to a number
USARTWriteChar('+');
USARTWriteChar('C');
USARTWriteChar('M'); // AT+CMGS=Mobile no.<carrige return>to

which return msg is to be send
USARTWriteChar('G');

USARTWriteChar('S');
USARTWriteChar('=');
USARTWriteChar('"');
USARTWriteChar('+');
USARTWriteChar('9');
USARTWriteChar('1');
USARTWriteChar('9');
USARTWriteChar('7');
USARTWriteChar('1');
USARTWriteChar('7');
USARTWriteChar('9');
USARTWriteChar('8');
USARTWriteChar('8');
USARTWriteChar('5');
USARTWriteChar('2');

USARTWriteChar('0');
USARTWriteChar('"');
USARTWriteChar('\n\r');

wait(5);

USART_StringTransmit(lattitude[11]);
USARTWriteChar(" ");
USART_StringTransmit(longitude[11]);


USARTWriteChar(26); // ASCII for Ctrl+Z

USARTWriteChar('\n\r');

wait(2);

USARTWriteChar('A');
USARTWriteChar('T');
USARTWriteChar('+'); // Sending AT Command AT+CMGD=1 to the

modem

USARTWriteChar('C');
USARTWriteChar('M'); // to delete inbox msg. at position no.1
USARTWriteChar('G');
USARTWriteChar('D');
USARTWriteChar('=');
USARTWriteChar('1');

USARTWriteChar('\n\r');

wait(2);
lcd_clrscr(); //celar screen
lcd_puts("Msg Deleted");

wait(2);
lcd_clrscr();
wait(2);;
}
}
}
