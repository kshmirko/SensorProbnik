#include <avr/io.h>
#include <avr/pgmspace.h>
#include "twi.h"
#include "uart.h"
#include "ssd1306.h"
#include "font.h"

int main(){

    i2c_init();
    SSD1306_Init();
    SSD1306_PutChar('A');
    UART_Init(9600);

    return 0;
}



