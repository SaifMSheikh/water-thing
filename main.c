#define NDEBUG//Comment this line out to enable UART.
#include"uart.h"
#include"led.h"
#include"lvl.h"
#define F_CPU 16000000//Arduino UNO clock frequency (required for delay).
#include<util/delay.h>//For `_delay_*()`.
int main(const int argc,const char**argv){
	uart_init();
	led_init();
	lvl_init();
	uint16_t wtr_lvl=0;//Real-time water level from sensor (%).
	const uint16_t ctl_lvl=375;//Water control threshold
	for(;1;){
		wtr_lvl=lvl_read();
		uart_uint(wtr_lvl);
		uart_line();
		if(wtr_lvl>=ctl_lvl)led_on();
		else led_off();
		_delay_ms(50);
	}
}
