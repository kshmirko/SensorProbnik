#include "ssd1306.h"
#include "twi.h"
#include <avr/pgmspace.h>
#include "font.h"


#ifdef SSD1306_BASE_FUNC
/**
 * Функция отправки управляющей последовательности дисплею
 * */
void SSD1306_Command(U08 cmd, U08 dat){

    i2c_start();

    i2c_send_byte((U08)SLA_W);

    i2c_send_byte(cmd);

    i2c_send_byte(dat);

    i2c_stop();
}

void SSD1306_Init(void){
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_DISPLAYOFF);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETDISPLAYCLOCKDIV);
    SSD1306_Command((U08)COMMAND, (U08)0x80);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETMULTIPLEX);
    SSD1306_Command((U08)COMMAND, (U08)0x3F);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETDISPLAYOFFSET);
    SSD1306_Command((U08)COMMAND, (U08)0x00);
    SSD1306_Command((U08)COMMAND, (U08)(SSD1306_SETSTARTLINE|0x00));
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_CHARGEPUMP);
    SSD1306_Command((U08)COMMAND, (U08)0x14);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_MEMORYMODE);
    SSD1306_Command((U08)COMMAND, (U08)0x00);
    SSD1306_Command((U08)COMMAND, (U08)(SSD1306_SEGREMAP|0x01));
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_COMSCANDEC);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETCOMPINS);
    SSD1306_Command((U08)COMMAND, (U08)0x12);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETCONTRAST);
    SSD1306_Command((U08)COMMAND, (U08)0xCF);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETPRECHARGE);
    SSD1306_Command((U08)COMMAND, (U08)0xF1);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_SETVCOMDETECT);
    SSD1306_Command((U08)COMMAND, (U08)0x40);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_DISPLAYALLOW_RESUME);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_NORMALDISPLAY);
    SSD1306_Command((U08)COMMAND, (U08)SSD1306_DISPLAYON);
}

void SSD1306_Clear(){
    i2c_start();
    i2c_send_byte(SLA_W);
    i2c_send_byte(DATA);
    
    U08 i, j;

    i = 8;
    do{
        j=128;
        do{
            i2c_send_byte(0);
            j--;
        }while(j>0);
        i--;
    }while(i>0);

    i2c_stop();
}

void SSD1306_GotoXY(U08 col, U08 row){
    SSD1306_Command(COMMAND, 0xB0 | row);
    SSD1306_Command(COMMAND, col & 0x0f);
    SSD1306_Command(COMMAND, 0x10 | (col >> 4));
}


void SSD1306_PutChar(U08 ch){
    
    U08 idx = ch - ASTART;
    idx = (U08)(idx * FONT_W);

    i2c_start();
    i2c_send_byte(SLA_W);
    i2c_send_byte(DATA);

    for(U08 i=idx; i<idx+FONT_W; i++){
        U08 tmp_byte = (U08)pgm_read_byte(&font[i]);
        i2c_send_byte(tmp_byte);
    }
    i2c_stop();
}

void SSD1306_PutStringZ(const S08 *str){
    while(*str){
        SSD1306_PutChar((U08)(*str++));
    }
}

#endif

#ifdef SSD1306_EXT_FUNC

void SSD1306_Set_Mode(U08 mode){
    if(mode==0){
        SSD1306_Command(COMMAND, SSD1306_NORMALDISPLAY);
    }else{
        SSD1306_Command(COMMAND, SSD1306_INVERTDISPLAY);
    }
}

void SSD1306_Set_Sleep(U08 sleep){
    if(sleep==0){
        SSD1306_Command(COMMAND, SSD1306_DISPLAYOFF);
    }else{
        SSD1306_Command(COMMAND, SSD1306_DISPLAYON);
    }
}

#endif
