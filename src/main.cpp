
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Configure le bit 6 du registre DDRD en sortie
  DDRD |= (1 << PD6);
  PORTD |= (1 << PD6);

  // Boucle infinie
  while (1) {
    PORTD &= 0;
    _delay_ms(1000);
    PORTD |= (1 << PD6);
    _delay_ms(1000);
  }
}
