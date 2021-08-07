#ifndef __SSD1306_H__
#define __SSD1306_H__



#define SSD1306_ADDR                0x3c
#define SLA_W                       SSD1306_ADDR << 1
#define SLA_R                       (SSD1306_ADDR << 1)|0x01   

#define TRUE                        0x01
#define FALSE                       0x00

#define SSD1306_LCDWIDTH            128
#define SSD1306_LCDHEIGHT           64
#define SSD1306_DEFAULT_SPACE       5

#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_DISPLAYON           0xAF
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_CHARGEPUMP          0x8D
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETCONTRAST         0x81
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_DISPLAYALLOW_RESUME 0xA4
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7
#define SSD1306_PAGEADDR            0x22
#define SSD1306_COLUMNADDR          0x12
#define COMMAND                     0x00
#define DATA                        0x40

#include "config.h"

/**
 *  Процедуры для рабрты с экраном 
 **/

#ifdef SSD1306_BASE_FUNC
void SSD1306_Init(void);
void SSD1306_Command(U08 cmd, U08 dat);
void SSD1306_Clear(void);
void SSD1306_GotoXY(U08 col, U08 row);
void SSD1306_PutChar(U08 ch);
#endif

#ifdef SSD1306_EXT_FUNC
void SSD1306_Set_Mode(U08 mode);
void SSD1306_Set_Sleep(U08 sleep);
void SSD1306_PutStringZ(const S08 *str);
#endif

#endif

