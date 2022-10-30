/* 
 * header.h
 * 
 * LED_Strobe
 * 
 *  2022.06.18
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef HEADER_H
#define	HEADER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/system/system.h"

#include "font12x16.h"
#include "font5x7.h"
#include "OLED_I2C_Q.h"





void    cmp1_int(void);
void    cmp2_int(void);





#endif	//HEADER_H

