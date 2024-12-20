#ifndef ETC_LVL_H
#define ETC_LVL_H
/**
 * The Water Level Sensor & ADC Interface.
 * Assumes 3.3V power to sensor.
 **/
#include<avr/io.h>
#include<stdint.h>
#define LVL_PRT PORTC
#define LVL_DDR DDRC
#define LVL_PIN 0
void lvl_init(){
	LVL_DDR&=~(1<<LVL_PIN);//Read sensor output.
	ADCSRA=0x8F;//ADC enabled,Clk/128.
	ADMUX=0x40;//Vref=Vcc, right-aligned, single-ended.
}
uint16_t lvl_read(){
	/*Perform Conversion*/
	ADCSRA|=(1<<ADSC);//Start conversion.
	while(!(ADCSRA&(1<<ADIF))){/*Wait For Conversion To Complete*/}
	/*Extract Result*/
	const uint8_t adc_lo=ADCL;
	const uint8_t adc_hi=ADCH;
	const uint16_t adc_in=(adc_hi<<8)|(adc_lo);
	ADCSRA|=(1<<ADIF);//Clear the interrupt flag.
	/*Scale Result*/
	return adc_in;
}

#endif
