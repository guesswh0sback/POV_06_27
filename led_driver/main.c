
#include <avr/io.h>
#include <util/delay.h>

// OE PC1
// SCK PB5
// LE PC2
// MOSI PB3

//setup spi
void spi_init(){
    DDRB |= (1 << PB3) | (1 << PB5); //set MOSI and SCK as Output
    DDRC |= (1 << PC2) | (1 << PC1); //set LE and OE as Output
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); //enable spi, set as master, set clock rate fck/16
}
void spi_send(uint8_t data){
    SPDR = data; //load data for transmission
    while(!(SPSR & (1 << SPIF))); //wait for transmission complete
}
void spi_send_big(uint16_t data){
    spi_send((data >> 8) & 0xFF); //send high first
    spi_send(data & 0xFF);        //send low last
}

// data de la forme led15_led14_led13_led12_led11_led10_led9_led8_led7_led6_led5_led4_led3_led2_led1_led0
void send_data(uint16_t data) {
    spi_send_big(data); //fonction send 16 bits data
    PORTC |= (1 << PC2); //load enable
    PORTC &= ~(1 << PC2); //disable enable
}

void leds_on(){
    PORTC &= ~(1 << PC1); //OE low
}
void leds_off(){
    PORTC |= (1 << PC1); //OE high
}

void display(uint16_t data){
    leds_off();
    send_data(data);
    leds_off();
}

uint16_t A = 0b1010101010101010;
uint16_t B = 0b0101010101010101;

int main(void) {
    while (1)
    {
        display(A);
        _delay_ms(1000);
        display(B);
        _delay_ms(1000);
    }
    return(0);
}
