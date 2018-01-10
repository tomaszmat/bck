#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h>

void USART_INIT( unsigned int ubrr );
void USART_TransmitChar( unsigned char data );
void Usart_sen_str(unsigned char* data, unsigned int len);
