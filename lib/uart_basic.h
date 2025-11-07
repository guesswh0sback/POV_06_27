#ifndef UART_BASIC_H
#define UART_BASIC_H

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(uint32_t baudrate);

void uart_send_byte(uint8_t byte);

void uart_send_string(char * str);

unsigned char USART_Receive(void);

void USART_Receive_string(char *buffer);

#endif /* UART_BASIC_H */