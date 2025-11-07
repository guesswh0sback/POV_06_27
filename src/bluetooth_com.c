#include "../lib/bluetooth_com.h"

#define NAME POV27
#define PIN 0027
#define BAUDRATE 38400


void BLUETOOTH_setup(uint32_t baudrate){
    USART_Init(baudrate);
    _delay_ms(100); //wait for the module to be ready
    PORTC |= (1 << PC0); //set key high
    

}