#include <avr/io.h>
#include <util/delay.h>
#include "dht11.h"
#include <avr/interrupt.h>

#define nop() asm volatile ("nop")

#include "config.h"
static inline void Delay18ms(void);
static inline void Delay54us(void);
static inline void Delay80us(void);
static inline void Delay30us(void);
static inline void Delay10us(void);
/*U08 dht11_read_byte(void);*/

U08 dht11_get_data(S08 *temp, U08 *hum){
    DHT_DDR &= ~(U08)(1<<DHT_BIT);
    DHT_PORT &=~ (U08)(1<<DHT_BIT);

    if(!(DHT_PIN & (U08)(1<<DHT_BIT))){
        Delay10us();
        if(!(DHT_PIN & (U08)(1<<DHT_BIT))) return DHT_READ_FAIL;
    }

    //Start signal
	DHT_DDR |= (U08)(1<<DHT_BIT);
	Delay18ms();	
	DHT_DDR &=~ (U08)(1<<DHT_BIT);
	Delay54us();
	if(DHT_PIN & (U08)(1<<DHT_BIT)) {
		return DHT_READ_FAIL;
	}
	while(!(DHT_PIN & (U08)(1<<DHT_BIT)));
	while(DHT_PIN & (U08)(1<<DHT_BIT));
	
	//Data bytes
	U08 DHT11_RH_integral = dht11_read_byte();
	U08 tmp = dht11_read_byte();
	U08 DHT11_T_integral  = dht11_read_byte();
	tmp = dht11_read_byte();
	U08 crc = dht11_read_byte();
	

	*hum = DHT11_RH_integral;
	*temp = (S08)DHT11_T_integral;
    
    if ((DHT11_RH_integral+DHT11_T_integral)!=crc){
        return DHT_CRC_FAIL;
    }

    return DHT_READ_OK;
}


static inline void Delay18ms(void){
    cli();
    asm volatile (
        "    ldi  r18, 2	\n"
        "    ldi  r19, 119	\n"
        "    ldi  r20, 3	\n"
        "1:  dec  r20	\n"
        "    brne 1b	\n"
        "    dec  r19	\n"
        "    brne 1b	\n"
        "    dec  r18	\n"
        "    brne 1b	\n"
        "    nop	\n"
    );
    
    sei();

}

static inline void Delay54us(void){
    cli();
    
    asm volatile (
        "    ldi  r18, 2	\n"
        "    ldi  r19, 29	\n"
        "2:  dec  r19	\n"
        "    brne 2b	\n"
        "    dec  r18	\n"
        "    brne 2b	\n"
        "    rjmp 2f	\n"
        "2:	\n"
    );
    sei();
}

static inline void Delay80us(void){
    cli();

    asm volatile (
        "    ldi  r18, 2	\n"
        "    ldi  r19, 168	\n"
        "3:  dec  r19	\n"
        "    brne 3b	\n"
        "    dec  r18	\n"
        "    brne 3b	\n"
        "    nop	\n"
    );
    sei();
}

static inline void Delay30us(void){
    cli();
    asm volatile (
        "    ldi  r18, 159	\n"
        "4:  dec  r18	\n"
        "    brne 4b	\n"
        "    nop        \n"
    );
    sei();
}

static inline void Delay10us(void){
    cli();
    asm volatile (
        "    ldi  r18, 52	\n"
        "5:  dec  r18	\n"
        "    brne 5b	\n"
        "    rjmp 5f	\n"
        "5:	\n"
    );
    sei();
}


U08 dht11_read_byte(void){
    U08 dht11_data=0x00;
    U08 dht11_counter = 0;
        
    DHT_DDR &= ~(1<<DHT_BIT);
    for(U08 i=(U08)7; i>=0; i--){
        dht11_counter = 0;

        while(!(DHT_PIN & (1<<DHT_BIT)) && (dht11_counter<10)){
            Delay10us();
            dht11_counter++;
        }
        dht11_counter = 0;
        while((DHT_PIN & (1<<DHT_BIT)) && (dht11_counter<15)){
            Delay10us();
            dht11_counter++;
        }
        if(dht11_counter>5){
            dht11_data|=(1<<i);
        }

    }
    return (U08)dht11_data;
}
