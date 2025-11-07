#include "../lib/uart_basic.h"


void USART_Init(uint32_t baudrate){
    /* Init registers */
    UBRR0H =0;
    UBRR0L =0;
    UCSR0B =0;
    UCSR0A =0;
    UCSR0C =0;
    /* Set baud rate */
    unsigned int ubrr = (unsigned int)(16000000/8/baudrate-1);
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Disable parity bit */
    UCSR0A &= ~(1<<UPE0);
    /* Enable x2 speed */
    UCSR0A |= (1<<U2X0); 
    /* Set frame format: 8data, 1stop bit */
    UCSR0C &= ~(1<<USBS0); 
    UCSR0C |= (3<<UCSZ00);
}

void uart_send_byte(uint8_t byte){
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0))){}
        /* Put data into buffer, sends the data */
        UDR0 = byte;
    
}

void uart_send_string(char * str){
    int i = 0;
    while (str[i] != '\0')
    {
        uart_send_byte(str[i]);
        i++;
    }
    
}

unsigned char USART_Receive(void){
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0))){}
    /* Get and return received data from buffer */
    return UDR0;
}

void USART_Receive_string(char *buffer, int size){
    int indice = size - 1;
    while (indice > 0)
    {
        buffer[indice] = USART_Receive();
        indice--;
    }

}