#include "hall.h"

int COUNTER = 0;

void HALL_init(){
    DDRD &= ~(1 << PD2); //set PD2 (INT0) as input
    PORTD |= (1 << PD2); //enable pull-up on PD2

    EIMSK |= (1 << INT0); //enable external interrupt INT0
    EICRA |= (1 << ISC01) | (1 << ISC00); //trigger INT0 on rising edge
}

void TIMER1_init(){
    TCCR1A = 0; //normal mode
    TCCR1B |= (1 << WGM12); //CTC mode
    TCCR1B |= (1 << CS12); //prescaler 256
    OCR1A = 62500; //compare value for 1s at 13MHz with prescaler 256
    TIMSK1 |= (1 << OCIE1A); //enable compare interrupt
}

ISR(INT0_vect){
    //hall effect sensor triggered
    //handle event here
    COUNTER++;
}
