#ifndef __DHT11_H__
#define __DHT11_H__

#include <avr/io.h>

#define DHT_PORT    PORTB
#define DHT_BIT     PINB0
#define DHT_DDR     DDRB
#define DHT_PIN     PINB

#define DHT_READ_OK     1
#define DHT_READ_FAIL   0
#define DHT_CRC_FAIL    2
#include "config.h"

U08 dht11_get_data(S08 *temp, U08 *hum);
#endif

