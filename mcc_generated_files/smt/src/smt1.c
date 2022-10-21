/**
 * SMT1 Generated Driver File
 *
 * @file smt1.c
 * 
 * @ingroup smt1 
 * 
 * @brief This file contains the driver code for SMT1 module.
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../smt1.h"

/**
  Section: SMT1 APIs
*/

void SMT1_Initialize(void)
{

    // SMTEN enabled; SMTSTP rolls over to 0x000000; SMTWPOL low/falling edge enabled; SMTSPOL low/falling edge enabled; SMTCPOL rising edge; SMTPS 1:1 Prescaler; 
    SMT1CON0 = 0x98;
    
    // SMTGO disabled; SMTREPEAT Single Acquisition mode; SMTMODE Time of flight; 
    SMT1CON1 = 0x6; 
    
    // SMTCPRUP SMT1PR1 update complete; SMTCPWUP SMT1CPW1 update complete; SMTRST SMT1TMR1 update complete; 
    SMT1STAT = 0x0; 
    
    // SMTCSEL FOSC; 
    SMT1CLK = 0x1; 
    
    // SMTWSEL C1OUT_sync; 
    SMT1WIN = 0x1D; 
    
    // SMTSSEL C2OUT_sync; 
    SMT1SIG = 0x1C; 
    
    // SMTPRU 0; 
    SMT1PRU = 0x0; 
    
    // SMTPRH 0; 
    SMT1PRH = 0x0; 
    
    // SMTPRL 0; 
    SMT1PRL = 0x0; 

    // Enabling SMT1 overflow interrupt.
    // PIE1bits.SMT1IE = 1;

    // Enabling SMT1 pulse width acquisition interrupt.
    // PIE1bits.SMT1PWAIE = 1; 

    // Enabling SMT1 period acquisition interrupt.
    // PIE1bits.SMT1PRAIE = 1; 

}
        
void SMT1_DataAcquisitionEnable(void)
{
    // Start the SMT module by writing to SMTxGO bit
    SMT1CON1bits.SMT1GO = 1;
}

void SMT1_DataAcquisitionDisable(void)
{
    // Stop the SMT module by writing to SMTxGO bit
    SMT1CON1bits.SMT1GO = 0;
}

void SMT1_HaltCounter(void)
{
    SMT1CON0bits.STP = 1;
}

void SMT1_SetPeriod(uint32_t periodVal)
{
    // Write to the SMT1 Period registers
    SMT1PRU = (uint8_t)(periodVal >> 16);
    SMT1PRH = (uint8_t)(periodVal >> 8);
    SMT1PRL = (uint8_t)periodVal;
}

uint32_t SMT1_GetPeriod(void)
{
    return (SMT1PR);
}

void SMT1_SingleDataAcquisition(void)
{
    SMT1CON1bits.SMT1REPEAT = 0;
}

void SMT1_RepeatDataAcquisition(void)
{
    SMT1CON1bits.SMT1REPEAT = 1;
}

void SMT1_ManualPeriodBufferUpdate(void)
{
    SMT1STATbits.SMT1CPRUP = 1;
}

void SMT1_ManualPulseWidthBufferUpdate(void)
{
    SMT1STATbits.SMT1CPWUP = 1;
}

void SMT1_ManualTimerReset(void)
{
    SMT1STATbits.RST = 1;
}

bool SMT1_IsWindowOpen(void)
{
    return (SMT1STATbits.SMT1WS);
}

bool SMT1_IsSignalAcquisitionInProgress(void)
{
    return (SMT1STATbits.SMT1AS);
}

bool SMT1_IsTimerIncrementing(void)
{
    return (SMT1STATbits.SMT1TS);
}

uint32_t SMT1_GetCapturedPulseWidth(void)
{
    return (SMT1CPW);
}

uint32_t SMT1_GetCapturedPeriod(void)
{
    return (SMT1CPR);
}

uint32_t SMT1_GetTimerValue(void)
{
    return (SMT1TMR);
}

void SMT1_PR_ACQ_ISR(void)
{
    
    // Disabling SMT1 period acquisition interrupt flag bit.
    PIR1bits.SMT1PRAIF = 0; 
}

void SMT1_PW_ACQ_ISR(void)
{
 
    // Disabling SMT1 pulse width acquisition interrupt flag bit.
    PIR1bits.SMT1PWAIF = 0; 
}

void SMT1_Overflow_ISR(void)
{
  
    // Disabling SMT1 overflow interrupt flag bit.
     PIR1bits.SMT1IF = 0; 
}
/**
 End of File
*/