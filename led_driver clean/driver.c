#include "driver.h"

// OE PC1
// SCK PB5
// LE PC2
// MOSI PB3

uint16_t A = 0b1010101010101010;
uint16_t B = 0b0101010101010101;

//setup spi
void SPI_init(){
    PORTB |= (1 << PB3) | (1 << PB5); //set MOSI and SCK as Output
    DDRC |= (1 << PC1) | (1 << PC2); //set LE and OE as Output
    PORTD |= (1 << PD6); //for test purposes only
    //SPCR =  (1 << SPE) | (1 << MSTR) | (1 << SPR0); //enable spi, set as master, set clock rate fck/16 (useless for our purpose)
}

void MOSI_on(){
    PORTB |= (1<<PB3); // MOSI HIGH
}
void MOSI_off(){
    PORTB &= ~(1<<PB3); // MOSI LOW
}
void LEDS_on(){
    PORTC &= ~(1 << PC1); //OE low
}
void LEDS_off(){
    PORTC |= (1 << PC1); //OE high
}
void CLK_rise(){
    PORTB |= (1 << PB5); //clk rise
}
void CLK_fall(){
    PORTB &= ~(1 << PB5); //clk fall
}
void LATCH_enable(){
    PORTC |= (1 << PC2); //latch enable
}
void LATCH_disabled(){
    PORTC &= ~(1 << PC2); //disable latch
}

void LEDS_on_test(){
    PORTD &= ~(1 << PD6);
}
void LEDS_off_test(){
    PORTD |= (1 << PD6);
}

void data_send_bourrin(uint16_t data){
    /* parse the data to find what leds must be on */
    for (int i = 15; i > 0; i--)
    {
        CLK_rise(); // rise for the i-th bit
        if(data & (1<<i)){ // looks only at the i-th value of data 
            MOSI_on();
        }
        else
        {
            MOSI_off();
        }
        CLK_fall(); // fall for the i-th bit       
        MOSI_off(); // reset MOSI to ensures standard logic level for the next bit
    }
    LATCH_enable(); // validate data sent to the led driver
    LATCH_disabled();  // 1 clk tick is enough
}

void display_bourrin(uint16_t data){
    LEDS_off();
    data_send_bourrin(data);
    set_brightness(0.5,1000);
}

void set_brightness(float percentage, int time_ms){
    int period = 100; //us
    for (int i = 0; i < (int)(time_ms*1000/period); i++){ // set brightness for 'time_ms' ms

        for (int i = 0; i < (int)(percentage*period); i++){ // PMW with 'percentage' duty cycle
            LEDS_on();
            _delay_us(1);
        }
        for (int i = 0; i < period-(int)(percentage*period); i++){
            LEDS_off();
            _delay_us(1);
        }

    }
}