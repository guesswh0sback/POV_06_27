#include "driver.h"
// OE PC1
// SCK PB5
// LE PC2
// MOSI PB3

//setup spi
void SPI_init(){
    DDRB |= (1 << PB3); 
    DDRB |= (1 << PB5); //set MOSI and SCK as Output
    PORTB |= (1 << PB3); 
    PORTB |= (1 << PB5); //set MOSI and SCK as Output
    DDRC |= (1 << PC1); 
    DDRC |= (1 << PC2); //set LE and OE as Output
    PORTC |= (1 << PB3); 
    PORTC |= (1 << PB5); //set MOSI and SCK as Output
    // PORTD |= (1 << PD6); //for test purposes only
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
        if(data & (1<<i)){ // looks only at the i-th value of data 
            MOSI_on();
        }
        else
        {
            MOSI_off();
        }
        CLK_rise(); // rise for the i-th bit
        CLK_fall(); // fall for the i-th bit       
        MOSI_off(); // reset MOSI to ensures standard logic level for the next bit
    }
    LATCH_enable(); // validate data sent to the led driver
    LATCH_disabled();  // 1 clk tick is enough
}


void set_brightness(float percentage, int time_ms){
    int period = 1000; //us
    for (int i = 0; i < (int)(time_ms*1000/period); i++){ // set brightness for 'time_ms' ms

        for (int i = 0; i < (int)(percentage*period); i++){ // PMW with 'percentage' duty cycle
            LEDS_on();
            _delay_us(1);
        }
        LEDS_off();
        for (int i = 0; i < period-(int)(percentage*period); i++){
            _delay_us(1);
        }

    }
}

void display_bourrin(uint16_t data, float percentage, int time_ms){
    LEDS_off();
    data_send_bourrin(data);
    set_brightness(percentage, time_ms);
}