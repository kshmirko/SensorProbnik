#ifndef __TWI_H__
#define __TWI_H__

#include "config.h"

#ifdef I2C_BASE_FUNC
    void i2c_init();
    void i2c_start();
    void i2c_stop();
    void i2c_restart();
    void i2c_send_byte(U08 ch);
    void i2c_wait_interrupt();
    U08 i2c_receive_byte();
    U08 i2c_receive_lastbyte();
#endif

#ifdef I2C_EXT_FUNC
    U08 i2c_get_status();
#endif


#endif
