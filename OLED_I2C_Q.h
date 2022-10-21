/* 
 * File:   OLED_I2C_Q.h
 * Comments: PIC18F27Q43
 * Revision history: 
 * 2022.10.09   
*/

#include    "header.h"


#define OLED_address     0x3c            // I2CÚ‘±¬Œ^OLED 128x64 ‚ÌƒAƒhƒŒƒX 0x3c + Write bit0->0 = 0x78

extern bool baikaku;


void OLED_init(void);
void OLED_clr(void);

void locate(uint8_t, uint8_t);
void locate6x8(uint8_t, uint8_t);
void locate6x16(uint8_t, uint8_t);

void putch_OLED(uint8_t);
void chr57(uint8_t);
void chr57D(uint8_t);
uint16_t bitmap2x(uint8_t);


