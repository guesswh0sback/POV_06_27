#include "../lib/hall.h"


volatile uint16_t last_time = 0;
volatile uint16_t current_time = 0;
volatile uint16_t time_diff = 0;
volatile uint8_t first_capture = 1;

void HALL_init(){
    DDRD &= ~(1 << PD2); //set PD2 (INT0) as input
    PORTD |= (1 << PD2); //enable pull-up on PD2

    EIMSK |= (1 << INT0); //enable external interrupt INT0
    EICRA |= (1 << ISC01) | (1 << ISC00); //trigger INT0 on rising edge
}

void TIMER1_init(){
    TCCR1A = 0; //normal port operation
    TCCR1B |= (1 << WGM12); //CTC mode
    TCCR1B |= (1 << CS12); //prescaler 256 (0bXXX<<CS10)
    OCR1A = 62500; //compare value for 1s at 13MHz with prescaler 256
    TIMSK1 |= (1 << OCIE1A); //enable compare interrupt
}

ISR(INT0_vect){
    current_time = TCNT1;

    display_bourrin(0b0101010101010101, 0.005, 100);

    if (first_capture){
        first_capture = 0;
    }
    else {
        if (current_time >= last_time)
            time_diff = current_time - last_time;
        else
            time_diff = (0xFFFF - last_time) + current_time + 1; // handle overflow
    }

    last_time = current_time;
}


