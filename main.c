/*
 *      LED_Strobe_v2
 *          with Start Trigger
 *          with Muzzle Velocity 
 * 
 *          Fosc 64MHz (Xtal:16MHz x4PLL)
 * 
 *  2022.06.11  ver.0.01    PWM��LED��_��
 *  2022.06.18  ver.0.10    �g���K�[�C���v�b�g�ǉ�
 *                          98m/s�Ή� 10kHz duty10%  ����100usec �p���X10usec   (v0=100m/s��10mm��)
 *                          PWM1PR:0x18ff = 6399, PWM1S1P1:0x0280 = 640
 *  2022.06.20  ver.0.11    43m/s�Ή� 5kHz duty10%  ����200usec �p���X10usec    (v0=50m/s��10mm��)
 *                          PWM1PR:12799, PWM1S1P1:0x0280 = 640
 *  2022.06.20  ver.0.12    26m/s�Ή��@2.5kHz duty10%  ����400usec �p���X10usec�@(v0=25m/s��10mm��)
 *                          PWM1PR:25599, PWM1S1P1:0x0280 = 640
 *  2022.06.20  ver.0.13    34m/s�Ή��@3.3kHz duty10%  ����300usec �p���X10usec�@(v0=33m/s��10mm��)
 *                          PWM1PR:19199, PWM1S1P1:0x0280 = 640
 *  2022.06.24  ver.0.14    DEBUGger�\���̃^�C�~���O���B�e�ɓK����悤�ɕύX�B
 *                          ���������������Ōv�Z���A12mm�Ԋu�Ɏʂ�悤�ɁB
 *  2022.06.25  ver.0.20    MCC�̃g���u���̂���_v2�ɃR�s�[
 *  2022.06.25  ver.0.21    �_�Ŕ�������������10msec->12msec VSR�̎����邭�Ȃ肷����
 *  2022.06.27  ver.0.22    �����p���X10us��5us�B�����񐔂̐����B
 *  2022.07.30  ver.0.23    DEBUGger�̕\����1�s���Ƃ�����iOCR�Ή��j
 *  2022.07.31  ver.0.24    OCR�Ή������\���@()�Ȃ��A���Ԃ�����
 *  2022.08.19  ver.0.25    15�񔭌��ɕύX
 *  2022.10.08  ver.0.26    �^�}���j�p���d�X�C�b�`�o��(�R���p���[�^�o�� H:idel,L:ON)�@���苗��12mm
 *  2022.10.09  ver.0.27    I2C LCD OLED 128x32 �ǉ� I2C�m���u���b�NMCC�g�p
 *  2022.10.10  ver.0.28    putch��uart��OLED LCD�̗�����
 *  2022.10.16  ver.0.29    �����Z���T�o��BUGFIX �X���[���[�gmax
 *  2022.10.17  ver.0.30    SMT1�̓��̓G�b�W�̐ݒ�~�X�@rise �� fall �փo�O�t�B�N�X�B�^�}���j�ւ̏o��OK�B
 *  2022.10.21              github rakugaki0cam/LED_Strobe_v2�ցB
 *  2022.10.29  ver.0.31    �^�C���\�������_�ȉ�2���ɁB
 *  2022.10.29  ver.0.32    �t�H���g12x16������ǉ�
 *  2022.10.31  ver.0.33    �f�B�X�v���C�\������
 * 
 * 
 */

#include "mcc_generated_files/system/system.h"
#include "header.h"


/*
    Main application
*/
const char  version[] = "0.33"; 
bool        timer1_int_flag = 0;
bool        cmp1_int_flag = 0;
bool        cmp2_int_flag = 0;
uint32_t    t;
uint16_t    t_light;
double      v0, pe;

void cmp1_int(void){
    cmp1_int_flag = 1;
}

void cmp2_int(void){
    cmp2_int_flag = 1;
}


int main(void)
{
    SYSTEM_Initialize();    
    
#if (PWM_10KHZ == true)
    //PWM1_16BIT_WritePeriodRegister(6399);     //10kHz 100m/s
    //PWM1_16BIT_WritePeriodRegister(12799);    //5kHz   50m/s
    //PWM1_16BIT_WritePeriodRegister(25599);    //2.5kHz 25m/s
    PWM1_16BIT_WritePeriodRegister(19199);      //3.3kHz 30m/s
#endif
    
    //PWM pulse width
    //PWM1_16BIT_SetSlice1Output1DutyCycleRegister(640);    //10us  1/100000sec
    //PWM1_16BIT_SetSlice1Output1DutyCycleRegister(480);    //7.5us 1/133333sec
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(320);    //5us   1/200000sec

    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable();
  
    __delay_ms(1000);
    //LED_YELLOW_SetLow();
    //LED_WHITE_SetLow();
      
    OLED_init();        //��������
    OLED_clr();
    
    //OLED & deBUGger
    printf("\n");
    font_size = FONT5X7;
    locate(0, 0);
    printf("********************\n");
    locate(0, 1);
    printf(" LED Strobe v2      \n");
    locate(0, 2);
    printf("           ver.%s\n", version);
    locate(0, 3);
    printf("********************\n");
    printf("\n");

    __delay_ms(500);
    LED_BLUE_SetLow();
    __delay_ms(1500);
    OLED_clr();
    
#if FONT_TEST != 0
    font_size = FONT12;
    locate(0,0);
    printf("0123456789");
    locate(0,1);
    printf("123.4 /usm");
#endif
    
    cmp1_int_flag = 0;
    cmp2_int_flag = 0;
    PWM1_16BIT_Disable();
    SMT1_DataAcquisitionEnable();
    
    while(1)
    {
        if (cmp2_int_flag == 1){
            //auto period
            t = SMT1_GetCapturedPeriod();                                   //�B�e�Ԋu��12mm�Ԋu�ɂ���
            PWM1_16BIT_WritePeriodRegister((uint16_t)(t & 0x0000ffff));     //cmp2���I���������PWM���Ԃ��Z�b�g
            
            PWM1_16BIT_Enable();
            //�������ԃ^�C�}�[�̌v�Z(15�񔭌��@12mm x 14 = 168mm)
            t_light = 0xffff - (uint16_t)((t & 0x0000ffff) >> 1) + 0x10;    //TMR1 FOSC/4 pre1:8 �Ȃ̂�16�p���X���̃J�E���g�l��菭���Z������
            Timer1_Write(t_light);
            Timer1_Start();
            while(!Timer1_HasOverflowOccured()){
            }
            PWM1_16BIT_Disable();
            //Clear interrupt flags
            PIR3bits.TMR1IF = 0;
            Timer1_Stop();
            
            //
            //LED_YELLOW_SetHigh();
            //printf("sensor1 on\n");
            //LED_YELLOW_SetLow();
            
            //�����̌v�Z
#define SENSOR1_2   0.0120      //�Z���T�[�Ԋu�@m
            
            pe = (double)t / _XTAL_FREQ;
            v0 = SENSOR1_2 / pe;
            
            if ((v0 < 200) && (v0 > 0)){
                font_size = FONT12;
                locate(0,0);
                printf("%6.2f m/s", v0);
                locate(0,1);
                printf("%7.2f us", pe * 1000000);
                //DEBUGger��OLED�̗����ɕ\�����o���̂ŁA�������ɒ��ӁB
                //locate()��DEBUGger�ł͖����ɂȂ�
                
            }else {
                font_size = FONT5X14;
                locate(0,0);
                printf("v0:error");
            }
            
            //SMT1�ăZ�b�g
            SMT1_DataAcquisitionDisable();
            SMT1_DataAcquisitionEnable();
            
            //�J�����̃V���b�^�[���҂�
            __delay_ms(1000);
            
            OLED_clr(); 

            printf("\n");       //�B�e���ɃX�N���[�������Ȃ��B�@OCR�̂��߂�1�s����
            printf("\n");       //���s\n��OLED�ł͖����ƂȂ�
            //
            cmp1_int_flag = 0;
            cmp2_int_flag = 0;
        }
        
    }    
}


