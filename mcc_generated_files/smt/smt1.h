/**
 * SMT1 Generated Driver API Header File
 * 
 * @file smt1.h
 * 
 * @defgroup smt1 SMT1
 * 
 * @brief This file contains API prototypes and other datatypes for SMT1 module.
 *
 * @version SMT1 Driver Version 2.11
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

#ifndef SMT1_H
#define SMT1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: SMT1 APIs
*/

/**
 * @ingroup smt1
 * @brief This API initializes the SMT1 module and be called before any other SMT1 routines. This routine should only be called once during system initialization.
 * @param void
 * @return void
 */
void SMT1_Initialize(void);

/**
 * @ingroup smt1
 * @brief This routine is used to enable data acquisition.
 * @pre SMT1() should have been initialized before calling this function.
 * @param void
 * @return void
 */
void SMT1_DataAcquisitionEnable(void);

/**
 * @ingroup smt1
 * @brief This routine is used to disable data acquisition.
 * @pre SMT1() should have been initialized before calling this function.
 * @param void
 * @return void
 */
void SMT1_DataAcquisitionDisable(void);

/**
 * @ingroup smt1
 * @brief This routine allows the counter to be at SMT1PR and interrupt occurs when clocked.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @return void
 */
void SMT1_HaltCounter(void);

/**
 * @ingroup smt1
 * @brief This routine is used to change the period.
 * @pre SMT1() should have been initialized before calling this function.
 * @param uint32_t periodVal - period value to be loaded
 * @return void
 */
void SMT1_SetPeriod(uint32_t periodVal);

/**
 * @ingroup smt1
 * @brief This routine is used to get SMT1 period value.
 * @pre SMT1() should have been initialized before calling this function.
 * @param void
 * @return uint32_t - value of period register.
 */
uint32_t SMT1_GetPeriod(void);

/**
 * @ingroup smt1
 * @brief This routine allows single data acquisition.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @return void
 */
void SMT1_SingleDataAcquisition(void);

/**
 * @ingroup smt1
 * @brief This routine allows repeat data acquisition.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @return void
 */
void SMT1_RepeatDataAcquisition(void);

/**
 * @ingroup smt1
 * @brief This routine allows SMT1 to update SMT1PR registers.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @return void
 */
void SMT1_ManualPeriodBufferUpdate(void);

/**
 * @ingroup smt1
 * @brief This routine allows SMT1 to update SMT1CPW registers.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @return void
 */
void SMT1_ManualPulseWidthBufferUpdate(void);

/**
 * @ingroup smt1
 * @brief This routine allows SMT1 to reset SMT1TMR registers.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @return void
 */
void SMT1_ManualTimerReset(void);

/**
 * @ingroup smt1
 * @brief This routine is used to determine if SMT1 window is open or closed. This bit is only valid when TS bit equals to 1.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @retval 1 (true)  - SMT1 window is open
 * @retval 0 (false) - SMT1 window is closed
 */
bool SMT1_IsWindowOpen(void);

/**
 * @ingroup smt1
 * @brief This routine is used to determine if SMT1 signal acquisition is in progress or not. This bit is only valid when TS bit equals to 1.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @retval 1 (true)  - SMT1 signal acquisition is in progress
 * @retval 0 (false) - SMT1 signal acquisition is not in progress
 */
bool SMT1_IsSignalAcquisitionInProgress(void);

/**
 * @ingroup smt1
 * @brief This routine is used to determine if SMT1 timer is incrementing or not.
 * @pre SMT1() should have been initialized and data acquisition enabled before calling this function.
 * @param void
 * @retval 1 (true)  - SMT1 timer is incrementing
 * @retval 0 (false) - SMT1 timer is not incrementing
 */
bool SMT1_IsTimerIncrementing(void);

/**
 * @ingroup smt1
 * @brief This routine is used to get SMT1 pulse width latch register value.
 * @pre SMT1() should have been initialized before calling this function.
 * @param void
 * @return uint32_t - Value of pulse width latch register.
 */
uint32_t SMT1_GetCapturedPulseWidth(void);

/**
 * @ingroup smt1
 * @brief This routine is used to get SMT1 period latch register value.
 * @pre SMT1() should have been initialized before calling this function.
 * @param void
 * @return uint32_t - Value of period register.
 */
uint32_t SMT1_GetCapturedPeriod(void);

/**
 * @ingroup smt1
 * @brief This routine is used to get SMT1 Timer latch register value.
 * @pre SMT1() should have been initialized before calling this function.
 * @param void
 * @return uint32_t - Value of Timer register.
 */
uint32_t SMT1_GetTimerValue(void);

/**
 * @ingroup smt1
 * @brief This routine is used to implement the Period Acquisition Interrupt ISR for the interrupt-driven implementations.
 * @pre The SMT1 and Interrupt Manager should be initialized.
 * @param void
 * @return void
 */
void SMT1_PR_ACQ_ISR(void);

/**
 * @ingroup smt1
 * @brief This routine is used to implement the Pulse Width Acquisition Interrupt ISR for the interrupt-driven implementations.
 * @pre The SMT1 and Interrupt Manager should be initialized.
 * @param void
 * @return void
 */
void SMT1_PW_ACQ_ISR(void);

/**
 * @ingroup smt1
 * @brief This routine is used to implement the Counter Overflow Interrupt ISR for the interrupt-driven implementations.
 * @pre The SMT1 and Interrupt Manager should be initialized.
 * @param void
 * @return void
 */
void SMT1_Overflow_ISR(void);


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // SMT1_H
/**
 End of File
*/