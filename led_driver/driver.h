
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <avr/io.h>
#include <util/delay.h>

void SPI_init();
void MOSI_on();
void MOSI_off();
void LEDS_on();
void LEDS_off();
void CLK_rise();
void CLK_fall();
void LATCH_enable();
void LATCH_disabled();
void LEDS_on_test();
void LEDS_off_test();
void data_send_bourrin(uint16_t data);
void display_bourrin(uint16_t data, float brightness, int time_ms);
void set_brightness(float percentage, int time_ms);

#endif /* LED_DRIVER_H */   