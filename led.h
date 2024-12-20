#ifndef ETC_LED_H
#define ETC_LED_H
/**
 * LED interface
 **/
#include<avr/io.h>
/*LED attached to PB5 by default*/
#define LED_PIN 5
#define LED_PRT PORTB
#define LED_DDR DDRB
/*Basic LED Control*/
void led_init(){LED_DDR|=(1<<LED_PIN);}//Set LED pin to output
void led_on(){LED_PRT|=(1<<LED_PIN);}//Send HIGH to LED
void led_off(){LED_PRT&=~(1<<LED_PIN);}//Send LOW to LED
#endif
