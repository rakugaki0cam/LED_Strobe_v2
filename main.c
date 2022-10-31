/*
 *      LED_Strobe_v2
 *          with Start Trigger
 *          with Muzzle Velocity 
 * 
 *          Fosc 64MHz (Xtal:16MHz x4PLL)
 * 
 *  2022.06.11  ver.0.01    PWMでLEDを点灯
 *  2022.06.18  ver.0.10    トリガーインプット追加
 *                          98m/s対応 10kHz duty10%  周期100usec パルス10usec   (v0=100m/sで10mm毎)
 *                          PWM1PR:0x18ff = 6399, PWM1S1P1:0x0280 = 640
 *  2022.06.20  ver.0.11    43m/s対応 5kHz duty10%  周期200usec パルス10usec    (v0=50m/sで10mm毎)
 *                          PWM1PR:12799, PWM1S1P1:0x0280 = 640
 *  2022.06.20  ver.0.12    26m/s対応　2.5kHz duty10%  周期400usec パルス10usec　(v0=25m/sで10mm毎)
 *                          PWM1PR:25599, PWM1S1P1:0x0280 = 640
 *  2022.06.20  ver.0.13    34m/s対応　3.3kHz duty10%  周期300usec パルス10usec　(v0=33m/sで10mm毎)
 *                          PWM1PR:19199, PWM1S1P1:0x0280 = 640
 *  2022.06.24  ver.0.14    DEBUGger表示のタイミングを撮影に適するように変更。
 *                          発光周期を初速で計算し、12mm間隔に写るように。
 *  2022.06.25  ver.0.20    MCCのトラブルのため_v2にコピー
 *  2022.06.25  ver.0.21    点滅発光持続総時間10msec->12msec VSRの時明るくなりすぎる
 *  2022.06.27  ver.0.22    発光パルス10us→5us。発光回数の制限。
 *  2022.07.30  ver.0.23    DEBUGgerの表示を1行ごとあける（OCR対応）
 *  2022.07.31  ver.0.24    OCR対応文字表示　()なし、隙間あける
 *  2022.08.19  ver.0.25    15回発光に変更
 *  2022.10.08  ver.0.26    タマモニ用光電スイッチ出力(コンパレータ出力 H:idel,L:ON)　測定距離12mm
 *  2022.10.09  ver.0.27    I2C LCD OLED 128x32 追加 I2CノンブロックMCC使用
 *  2022.10.10  ver.0.28    putchをuartとOLED LCDの両方へ
 *  2022.10.16  ver.0.29    初速センサ出力BUGFIX スルーレートmax
 *  2022.10.17  ver.0.30    SMT1の入力エッジの設定ミス　rise → fall へバグフィクス。タマモニへの出力OK。
 *  2022.10.21              github rakugaki0cam/LED_Strobe_v2へ。
 *  2022.10.29  ver.0.31    タイム表示小数点以下2桁に。
 *  2022.10.29  ver.0.32    フォント12x16数字を追加
 *  2022.10.31  ver.0.33    ディスプレイ表示整理
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
      
    OLED_init();        //割込許可後
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
            t = SMT1_GetCapturedPeriod();                                   //撮影間隔を12mm間隔にする
            PWM1_16BIT_WritePeriodRegister((uint16_t)(t & 0x0000ffff));     //cmp2がオンした後にPWM時間をセット
            
            PWM1_16BIT_Enable();
            //発光時間タイマーの計算(15回発光　12mm x 14 = 168mm)
            t_light = 0xffff - (uint16_t)((t & 0x0000ffff) >> 1) + 0x10;    //TMR1 FOSC/4 pre1:8 なので16パルス分のカウント値より少し短くする
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
            
            //初速の計算
#define SENSOR1_2   0.0120      //センサー間隔　m
            
            pe = (double)t / _XTAL_FREQ;
            v0 = SENSOR1_2 / pe;
            
            if ((v0 < 200) && (v0 > 0)){
                font_size = FONT12;
                locate(0,0);
                printf("%6.2f m/s", v0);
                locate(0,1);
                printf("%7.2f us", pe * 1000000);
                //DEBUGgerとOLEDの両方に表示を出すので、書き方に注意。
                //locate()はDEBUGgerでは無効になる
                
            }else {
                font_size = FONT5X14;
                locate(0,0);
                printf("v0:error");
            }
            
            //SMT1再セット
            SMT1_DataAcquisitionDisable();
            SMT1_DataAcquisitionEnable();
            
            //カメラのシャッター閉じ待ち
            __delay_ms(1000);
            
            OLED_clr(); 

            printf("\n");       //撮影中にスクロールさせない。　OCRのために1行あけ
            printf("\n");       //改行\nはOLEDでは無効となる
            //
            cmp1_int_flag = 0;
            cmp2_int_flag = 0;
        }
        
    }    
}


