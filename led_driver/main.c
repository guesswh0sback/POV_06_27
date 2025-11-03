
#include <avr/io.h>
#include <util/delay.h>

// OE PC1
// SCK PB5
// LE PC2
// MOSI PB3


// data de la forme led15_led14_led13_led12_led11_led10_led9_led8_led7_led6_led5_led4_led3_led2_led1_led0
void send_data(uint16_t data) {
    //fonction send 16 bits data
    PORTC |= (1 << OE); //load enable

}


int main(void) {


}
