#include "hall.h"

int main(void) {
    HALL_init();
    TIMER1_init();
    while (1)
    {
        // Main loop can be empty as functionality is interrupt-driven
    }

    return 0;
}