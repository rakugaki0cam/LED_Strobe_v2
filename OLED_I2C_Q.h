/* 
 * File:   OLED_I2C_Q.h
 * Comments: PIC18F27Q43
 * Revision history: 
 * 2022.10.09   
*/

#ifndef OLED_I2C_Q_H
#define	OLED_I2C_Q_H


#include    "header.h"


#define OLED_address     0x3c            // I2C�ڑ����^OLED 128x64 �̃A�h���X 0x3c + Write bit0->0 = 0x78

typedef enum  {
    FONT5X7     = 1,    //�W���@�@���Ȃ菬�����@21����x4�s
    FONT5X14    = 2,    //�c�{�p�@21����x2�s
    FONT12      = 3,    //12x16�t�H���g�@10����x2�s
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