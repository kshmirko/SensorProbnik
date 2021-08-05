#include <avr/io.h>
#include <avr/interrupt.h>
#include "twi.h"

//ISR(TWI_vect){
//    
//}

#ifdef I2C_BASE_FUNC

void i2c_init(){
    TWSR &= 0x00000000;
    TWBR = 72;
}

void i2c_start(){
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
}

void i2c_wait_interrupt(){
    while (!(TWCR & (1<<TWINT))) ;
}

void i2c_restart(){
    i2c_start();
}

void i2c_stop(){
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void i2c_send_byte(U08 ch){
    TWDR = ch;
    TWCR = (1<<TWINT)|(1<<TWEN);
    i2c_wait_interrupt();
}


U08 i2c_receive_byte(){
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    i2c_wait_interrupt();
    
    return (U08)TWDR;
}

U08 i2c_receive_lastbyte(){
    TWCR = (1<<TWEN)|(1<<TWINT);
    i2c_wait_interrupt();
    return (U08)TWDR;
}
#endif


#ifdef I2C_EXT_FUNC

U08 i2c_get_status(){
    return (U08)TWSR & 0xF8;
}

#endif

