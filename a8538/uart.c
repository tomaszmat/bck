#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h>

void USART_INIT( unsigned int ubrr )
{
	/* Set baud rate */

	UBRRL = 25;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN) |(1<<RXCIE);
	/* Set frame format:*/
	UCSRC = 0b10000110;
}
void USART_TransmitChar( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

	

void Usart_sen_str(unsigned char* data, unsigned int len)
{

	int i;

	for( i = 0; i<=len; i++)
	{
		USART_TransmitChar(data[i]);
	}	 
}
