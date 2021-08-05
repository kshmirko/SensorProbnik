#ifndef __UART_H__
#define __UART_H__

#include "config.h"

void UART_Init(U16 baud);
void UART_send_byte(U08 ch);
U08 UART_receive_byte();
void UART_Flush();

void UART_send_stringz(const S08 *strz);

#endif

