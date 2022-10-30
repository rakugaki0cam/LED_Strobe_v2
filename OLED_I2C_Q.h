/* 
 * File:   OLED_I2C_Q.h
 * Comments: PIC18F27Q43
 * Revision history: 
 * 2022.10.09   
*/

#ifndef OLED_I2C_Q_H
#define	OLED_I2C_Q_H


#include    "header.h"


#define OLED_address     0x3c            // I2C接続小型OLED 128x64 のアドレス 0x3c + Write bit0->0 = 0x78

typedef enum  {
    FONT5X7     = 1,    //標準　　かなり小さい　21文字x4行
    FONT5X14    = 2,    //縦倍角　21文字x2行
    FONT12      = 3,    //12x16フォント　10文字x2行
} fontsize_t;

extern fontsize_t   font_size;


void    OLED_init(void);
void    OLED_clr(void);

void    locate(uint8_t, uint8_t);
void    locate6x8(uint8_t, uint8_t);
void    locate6x16(uint8_t, uint8_t);
void    locate12x16(uint8_t, uint8_t);


void    putch_OLED(uint8_t);
void    chr57(uint8_t);
void    chr57D(uint8_t);
uint16_t bitmap2x(uint8_t);
void    chr12(uint8_t);
uint8_t ascii_font12(uint8_t);

#endif  //OLED_I2C_Q_H