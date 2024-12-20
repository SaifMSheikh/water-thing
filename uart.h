#ifndef ETC_UART_H
#define ETC_UART_H
/**
 * The UART Interface.
 * Only to be used for debugging.
 * Delays during transmission *will*
 * mess up application timings.
 * define NDEBUG to easily disable 
 * all UART actions.
 **/
#ifndef F_CPU 
#define F_CPU 16000000
#endif
#include<util/delay.h>
#include<avr/io.h>
#include<stdint.h>
#ifndef ETC_UART_MAX_DIGITS
#define ETC_UART_MAX_DIGITS 10
#endif
void uart_init(){
#ifndef NDEBUG
	UBRR0L=0xCF;//4800 baud
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);//Receiver/Transmitter mode
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);//8 data bits & 1 stop bit
#endif
}
void uart_send(const char*const str,const uint8_t len){
#ifndef NDEBUG
	for(uint8_t i=0;i<len;++i){
		while(!(UCSR0A&(1<<UDRE0)));	
		UDR0=str[i];
	}
#endif
}
void uart_line(){
#ifndef NDEBUG
	uart_send("\n\r",2);
#endif
}
void uart_print(const char*const str){
#ifndef NDEBUG
	for(uint8_t i=0;str[i]!='\0';++i){
		while(!(UCSR0A&(1<<UDRE0)));
		UDR0=str[i];
	}
#endif
}
void uart_println(const char*const str){
#ifndef NDEBUG
	uart_print(str);
	uart_line();
#endif
}
void uart_uint(uint16_t uint){
#ifndef NDEBUG
	char buf[ETC_UART_MAX_DIGITS];
	uint8_t idx=ETC_UART_MAX_DIGITS;
	do{/*Convert digits to characters*/
		buf[idx--]=(char)(uint%10)+'0';
	    uint/=10;
	}while(uint&&idx);
	uart_send(buf+idx+1,ETC_UART_MAX_DIGITS-idx);
#endif
}

#endif
