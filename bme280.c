#include "bme280.h"
#include "config.h"

S32 t_fine, dig_T1, dig_T2, dig_T3;

S32 bme_compensate_t_int32(S32 adc_T){

    S32 var1, var2, T;
    var1 = ((((adc_T>>3) - ((S32)dig_T1<<1))) * ((S32)dig_T2)) >> 11;

    var2 = (((((adc_T>>4) - ((S32)dig_T1)) * ((adc_T>>4) - ((S32)dig_T1))) >> 12) * ((S32)dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}
