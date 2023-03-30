#include "address_map_arm.h"


typedef struct ADC {
	int ch0;
	int ch1;
	
} ADC;

typedef struct _gpio{
	int data;
	int control;
} gpio;

volatile gpio* const port = (gpio*)JP1_BASE;
volatile ADC* const adcptr = (ADC *)ADC_BASE;
volatile int * const ledptr = (int *)LED_BASE;
volatile int* const swptr = (int *)SW_BASE;
volatile int* const display = (int *)HEX3_HEX0_BASE;

void hex_ps2(int count){
	
	int b5 = (count / 10)%10;
	int b6 = (count)%10;
	
	unsigned char seven_seg_decode_table[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	unsigned char hex_segs[] = { 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int shift_buffer, nibble;
	unsigned char code;
	int i;
	
	shift_buffer =(b5 << 4) | b6;
	for(i = 0; i < 6;i++){
	nibble = shift_buffer & 0x0000000F;
	code = seven_seg_decode_table[nibble];
	hex_segs[i] = code;
	shift_buffer = shift_buffer >> 4;
	}
	*(display) = *(int *)hex_segs;
}

int bitmask = 0xFFF;
volatile int DELAY_LENGTH;


int main(void){
	
volatile int delay_count;
volatile int status;

//Set pins to output
port->control = 1023;
int counter = 0;
DELAY_LENGTH = 70000;
status = 0;
while(1){
	
	adcptr->ch0 = 1;
	adcptr->ch1 = 1;
	//Display first channel
	while((*(swptr) == 0x2) | (*(swptr) == 0x03)){
		
	if(*(swptr) == 0x03){
		if(adcptr->ch0 &= bitmask){
		port->data = adcptr->ch0;
		counter--;
		if(counter < 5){
			if(counter < 0){
				counter = 0;
			}
			*(ledptr) = 0x000;
		}
		hex_ps2(counter);
		if(counter >= 5){
		*(ledptr) = 0xFF;
		*(display) = 0x713E3838;
	}
		
		while(*(swptr) == 0x03);
		}
		
		for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count);
	}
	}
		
	//Diplay second channel
	while((*(swptr) == 0x01) | (*(swptr) == 0x03)){
		
		if(*(swptr) == 0x03){
			if(adcptr->ch1 &= bitmask){
			port->data = adcptr->ch1;
			counter++;
			hex_ps2(counter);
			if(counter >= 5){
		counter = 5;
		*(ledptr) = 0xFF;
		*(display) = 0x713E3838;
	}
			
			while(*(swptr) == 0x03);
		}
	}
	
	       for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count);   
	}
	
}
}
	
