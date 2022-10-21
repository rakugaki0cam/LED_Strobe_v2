/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define PT1_TRIS                 TRISAbits.TRISA0
#define PT1_LAT                  LATAbits.LATA0
#define PT1_PORT                 PORTAbits.RA0
#define PT1_WPU                  WPUAbits.WPUA0
#define PT1_OD                   ODCONAbits.ODCA0
#define PT1_ANS                  ANSELAbits.ANSELA0
#define PT1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define PT1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define PT1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define PT1_GetValue()           PORTAbits.RA0
#define PT1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define PT1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define PT1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define PT1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define PT1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define PT1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define PT1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define PT1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)
   
// get/set RA1 aliases
#define PT2_TRIS                 TRISAbits.TRISA1
#define PT2_LAT                  LATAbits.LATA1
#define PT2_PORT                 PORTAbits.RA1
#define PT2_WPU                  WPUAbits.WPUA1
#define PT2_OD                   ODCONAbits.ODCA1
#define PT2_ANS                  ANSELAbits.ANSELA1
#define PT2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PT2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PT2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PT2_GetValue()           PORTAbits.RA1
#define PT2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PT2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PT2_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define PT2_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define PT2_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define PT2_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define PT2_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define PT2_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)
   
// get/set RA2 aliases
#define CMP1_OUT_TRIS                 TRISAbits.TRISA2
#define CMP1_OUT_LAT                  LATAbits.LATA2
#define CMP1_OUT_PORT                 PORTAbits.RA2
#define CMP1_OUT_WPU                  WPUAbits.WPUA2
#define CMP1_OUT_OD                   ODCONAbits.ODCA2
#define CMP1_OUT_ANS                  ANSELAbits.ANSELA2
#define CMP1_OUT_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define CMP1_OUT_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define CMP1_OUT_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define CMP1_OUT_GetValue()           PORTAbits.RA2
#define CMP1_OUT_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define CMP1_OUT_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define CMP1_OUT_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define CMP1_OUT_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define CMP1_OUT_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define CMP1_OUT_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define CMP1_OUT_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define CMP1_OUT_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)
   
// get/set RA3 aliases
#define CMP2_OUT_TRIS                 TRISAbits.TRISA3
#define CMP2_OUT_LAT                  LATAbits.LATA3
#define CMP2_OUT_PORT                 PORTAbits.RA3
#define CMP2_OUT_WPU                  WPUAbits.WPUA3
#define CMP2_OUT_OD                   ODCONAbits.ODCA3
#define CMP2_OUT_ANS                  ANSELAbits.ANSELA3
#define CMP2_OUT_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define CMP2_OUT_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define CMP2_OUT_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define CMP2_OUT_GetValue()           PORTAbits.RA3
#define CMP2_OUT_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define CMP2_OUT_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define CMP2_OUT_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define CMP2_OUT_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define CMP2_OUT_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define CMP2_OUT_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define CMP2_OUT_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define CMP2_OUT_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)
   
// get/set RB1 aliases
#define SCL_TRIS                 TRISBbits.TRISB1
#define SCL_LAT                  LATBbits.LATB1
#define SCL_PORT                 PORTBbits.RB1
#define SCL_WPU                  WPUBbits.WPUB1
#define SCL_OD                   ODCONBbits.ODCB1
#define SCL_ANS                  ANSELBbits.ANSELB1
#define SCL_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SCL_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SCL_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SCL_GetValue()           PORTBbits.RB1
#define SCL_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SCL_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)
   
// get/set RB2 aliases
#define SDA_TRIS                 TRISBbits.TRISB2
#define SDA_LAT                  LATBbits.LATB2
#define SDA_PORT                 PORTBbits.RB2
#define SDA_WPU                  WPUBbits.WPUB2
#define SDA_OD                   ODCONBbits.ODCB2
#define SDA_ANS                  ANSELBbits.ANSELB2
#define SDA_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SDA_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SDA_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SDA_GetValue()           PORTBbits.RB2
#define SDA_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SDA_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)
   
// get/set RB4 aliases
#define RX_TRIS                 TRISBbits.TRISB4
#define RX_LAT                  LATBbits.LATB4
#define RX_PORT                 PORTBbits.RB4
#define RX_WPU                  WPUBbits.WPUB4
#define RX_OD                   ODCONBbits.ODCB4
#define RX_ANS                  ANSELBbits.ANSELB4
#define RX_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RX_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RX_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RX_GetValue()           PORTBbits.RB4
#define RX_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RX_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define RX_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define RX_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define RX_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define RX_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RX_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)
   
// get/set RB5 aliases
#define TX_TRIS                 TRISBbits.TRISB5
#define TX_LAT                  LATBbits.LATB5
#define TX_PORT                 PORTBbits.RB5
#define TX_WPU                  WPUBbits.WPUB5
#define TX_OD                   ODCONBbits.ODCB5
#define TX_ANS                  ANSELBbits.ANSELB5
#define TX_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define TX_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define TX_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define TX_GetValue()           PORTBbits.RB5
#define TX_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define TX_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define TX_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define TX_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define TX_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define TX_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define TX_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)
   
// get/set RC3 aliases
#define LED_BLUE_TRIS                 TRISCbits.TRISC3
#define LED_BLUE_LAT                  LATCbits.LATC3
#define LED_BLUE_PORT                 PORTCbits.RC3
#define LED_BLUE_WPU                  WPUCbits.WPUC3
#define LED_BLUE_OD                   ODCONCbits.ODCC3
#define LED_BLUE_ANS                  ANSELCbits.ANSELC3
#define LED_BLUE_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define LED_BLUE_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define LED_BLUE_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define LED_BLUE_GetValue()           PORTCbits.RC3
#define LED_BLUE_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define LED_BLUE_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define LED_BLUE_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define LED_BLUE_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define LED_BLUE_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define LED_BLUE_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define LED_BLUE_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define LED_BLUE_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)
   
// get/set RC4 aliases
#define STROBE_TRIS                 TRISCbits.TRISC4
#define STROBE_LAT                  LATCbits.LATC4
#define STROBE_PORT                 PORTCbits.RC4
#define STROBE_WPU                  WPUCbits.WPUC4
#define STROBE_OD                   ODCONCbits.ODCC4
#define STROBE_ANS                  ANSELCbits.ANSELC4
#define STROBE_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define STROBE_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define STROBE_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define STROBE_GetValue()           PORTCbits.RC4
#define STROBE_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define STROBE_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define STROBE_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define STROBE_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define STROBE_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define STROBE_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define STROBE_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define STROBE_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)
   
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/