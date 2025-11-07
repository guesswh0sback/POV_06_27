#include <avr/io.h>
#include <util/delay.h>

#include "../lib/driver.h"


uint16_t A = 0b1000000000000000;
uint16_t B = 0b0100000000000000;
uint16_t C = 0b0010000000000000;
uint16_t D = 0b0001000000000000;
uint16_t E = 0b0000100000000000;
uint16_t F = 0b0000010000000000;
uint16_t G = 0b0000001000000000;
uint16_t H = 0b0000000100000000;
uint16_t I = 0b0000000010000000;
uint16_t J = 0b0000000001000000;
uint16_t K = 0b0000000000100000;
uint16_t L = 0b0000000000010000;
uint16_t M = 0b0000000000001000;
uint16_t N = 0b0000000000000100;
uint16_t O = 0b0000000000000010;
uint16_t P = 0b0000000000000001;

int main(void) {
        SPI_init();
    while (1)
    {  
        display_bourrin(A, 0.005, 100);
        display_bourrin(B, 0.005, 87);
        display_bourrin(C, 0.005, 75);
        display_bourrin(D, 0.005, 65);
        display_bourrin(E, 0.005, 57);
        display_bourrin(F, 0.005, 49);
        display_bourrin(G, 0.005, 43);
        display_bourrin(H, 0.005, 37);
        display_bourrin(I, 0.005, 32);
        display_bourrin(J, 0.005, 28);
        display_bourrin(K, 0.005, 24);
        display_bourrin(L, 0.005, 21);
        display_bourrin(M, 0.005, 18);
        display_bourrin(N, 0.005, 16);
        display_bourrin(O, 0.005, 14);
        display_bourrin(P, 0.005, 10);
            
    }

    return(0);
    
}
