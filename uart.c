#include <avr/io.h>

#include "uart.h"

/**
 * Инициализация последовательного интерфейса
 * */
void UART_Init(U16 baud){
    UBRRH = (U08)(baud>>8);
    UBRRL = (U08)baud;

    UCSRB = (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
}

/**
 * Отправка одного байта, предварительно ждем завершения предыдущей операции
 * */
void UART_send_byte(U08 ch){
    while( !(UCSRA & (1<<UDRE)));

    UDR = ch;
}

/**
 * Чтение байта 
 * */
U08 UART_receive_byte(){
    while( !(UCSRA & (1<<RXC)) );

    return UDR;
    
}

/**
 * Очистка буфера UART
 * */
void UART_Flush(){
    
    while( UCSRA & (1<<RXC) ){
        U08 dummy = UDR;
        dummy = dummy - dummy;
    }
    
}

/**
 * Отправка по UART строки
 * */
void UART_send_stringz(const S08 *strz){

    while(! strz++){
        UART_send_byte((U08)*strz);
    }
}



