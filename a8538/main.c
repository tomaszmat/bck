#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#include "uart.h"
#include "iic.h"
#include <util/twi.h>

#define F_CPU 1000000L 
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1 

#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)


#define ADDR_SENS 0x0b
void config(void);
void uart_test(void);

char* los = "dzgdgzdfgfdsggh5mzxcnbjwuen";
unsigned int cnt = 0;
uint8_t check =0;

int8_t raw_x = 0;
int8_t raw_y = 0;
int8_t raw_z = 0;
int8_t raw_w = 0;

unsigned char* str_out;
unsigned char* str_out2;
unsigned char* str_out3;
unsigned char* str_out4;

void cnf_led(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
}

int main(void)
{
	USART_INIT(MYUBRR); 
	Usart_sen_str("AtMEGA8535 Init\n", 16);

	i2c_init();
	Usart_sen_str("OK1\n", 3);

	check = i2c_start(ADDR_SENS+I2C_WRITE);
	//--------
	if (check == 1) Usart_sen_str("OK2\n", 3);
	else Usart_sen_str("!OK2\n", 4);
	//------

	i2c_stop();

	_delay_ms(1000);

	check = i2c_start(ADDR_SENS+I2C_READ);

	if (check == 1) Usart_sen_str("OK3\n", 3);
	else Usart_sen_str("!OK3\n", 4);

	raw_x = i2c_readByte();
	i2c_write2(TW_MT_DATA_ACK);

	raw_z = i2c_readByte();
	i2c_write2(TW_MT_DATA_ACK);

	raw_y = i2c_readByte();
	i2c_write2(TW_MT_DATA_ACK);

	raw_w = i2c_readByte();
	i2c_write2(TW_MT_DATA_ACK);

	i2c_stop();

	itoa( raw_x, str_out, 2 );
	itoa( raw_y, str_out2, 2 );
	itoa( raw_z, str_out3, 2 );
	itoa( raw_w, str_out4, 2 );

	Usart_sen_str(raw_x, 8);
	PORTB = raw_x;
	USART_TransmitChar('\n');
	_delay_ms(500);

	Usart_sen_str(raw_y, 8);
	PORTB = raw_y;
	USART_TransmitChar('\n');
	_delay_ms(500);

	Usart_sen_str(raw_z, 8);
	PORTB = raw_z;
	USART_TransmitChar('\n');
	_delay_ms(500);

	Usart_sen_str(raw_w, 8);
	PORTB = raw_w;
	USART_TransmitChar('\n');

	
	//config();
	while(1)
	{
		uart_test();
	}	
}


void config(void)
{
		DDRD &= ~(1<<PD2); //PD2 jako wejœcie
		PORTD |= (1<<PD2); //pull-up na PD2

		MCUCR |= (1<<ISC00); //reakcja INT0 na dowolne zbocze
		GICR |= (1<<INT0); //odblokowanie przerwania INT0
		TIMSK |= (1<<TOIE0); //odblokowanie przerwania od przepe³nienia T/C0
		sei(); //globalne odblokowanie przerw
		TCCR0 |= (1<<CS00); 
}

void uart_test(void)
{

	//if( check == 1) Usart_sen_str("OK\n", 3);
///	else Usart_sen_str("!OK\n", 4);
/*
	Usart_sen_str("TOMASZ MATUSIAK\n", 15);
	USART_TransmitChar('\r');
	USART_TransmitChar('\n');

	*/
		_delay_ms(50);
}



/*
ISR(INT0_vect) //podprogram obs³ugi INT0
{
 USART_TransmitChar(los[cnt]);

}

ISR(TIMER0_OVF_vect)
{
 cnt++;
 if(cnt == 20) cnt= 0;

}
*/
