/*
 *File:   OLED_I2C_2.c
 *
 * 	Graphic OLED ���W���[��
 *    I2C SSD1306
 *
 *  PIC18F27Q43
 * 
 * ����
 * 2022.10.09   MoMoni_CAN_26K83���PIC18F27Q43�ֈڐA
 *              �m���u���b�L���O�̂��߁A������I2C1_Write()����ƁAbusy�ɂĖ߂��Ă��Ă��܂��B
 *              ����O��I2C1_IsBusy()�Ńt���[�ɂȂ�܂ő҂B
 *              ���M��������O�Ƀf�[�^���������Ă��܂��Ɛ������\������Ȃ��B
 *              �Ƃ肠���������܂ő҂�����B
 * 2022.10.10   UART��putch����Ă΂��B\n���䕶�������O
 * 
 * 
 * 
 * 
 */

#include    "OLED_I2C_Q.h"

#define     contrast    30   //127���ƘI�o�I�[�o�[ISO400�@f2.8 1/1.6�@60�ł����I�[�o�[

//�n�[�h�̑I��
//#define     DISPLAYHEIGHT   64      //128x64 OLED
#define     DISPLAYHEIGHT   32      //128x32 OLED
//�����̑傫��(�s��)
bool        baikaku = 0;            //�c�{�p�@128x32 OLED�̎��͕\��2�s�ɂȂ�


void OLED_init(void){
    //OLED�̏�����
    i2c_host_error_t err;
    uint8_t da[10] = {
        0x00,           // Control byte bit7:Co=0, bit6:Data/Command#=0[command]
                        // Co=0 �Ƃ���ƈȌ�A������1�o�C�g�������
                        // Co=1 �Ƃ����1�o�C�g���閈��Control byte ������K�v������
        0x81, contrast, // Set contrast
        0x8d,           // Set charge pump
#if DISPLAYHEIGHT == 32
        //128x32 OLED
        0xa8, 31,       //set MUXratio=32   
        0xda, 0x02,     //set COMpin 128x32�p  {�d�v}
#endif
#if DISPLAYHEIGHT == 64  
    //128x64 OLED
        0xa8, 63,       //set MUXratio=64
        0xda, 0x12,     //set COMpin default
#endif    
        0x14,           // Enable charge pump
        0xaf            // Display ON
    };                  // ���̑��̏����ݒ�l�̓f�t�H���g
                        
    /*
    //2.24inch�p
    OLED_reset_SetLow();
    __delay_ms(20);
    OLED_reset_SetHigh();
    __delay_ms(200);
    */
    
    err = I2C1_ErrorGet();
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, da, 10);
    while(I2C1_IsBusy());   //�������ݏ������I���Ȃ������Ƀf�[�^��G�点�Ȃ��悤�ɑ҂��Ƃ���
    
    return;
}


void OLED_clr(void) {
    // OLED ��ʏ���
    uint8_t    i;
    uint8_t     clr[129];
    uint8_t     da[9] = {
        0x00,               //Co=0, D/C=0
        0x20, 0x00,         //set Horizontal addressing mode
        0x21, 0x00, 0x7f,   //set Column    start:0 end:127
        0x22, 0x00, 0x07    //Set page      start:0 end:7
    };
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, da, 9); 
    //while(I2C1_IsBusy());///////////////////////

    clr[0] = 0x40;                  //Control byte bit7:Co=0, bit6:Data/Command#=1[data VRAM�֏���]
    for(i = 1; i <= 128; i++){      // 128column
        clr[i] = 0x00;              // clear
    }
    
    for(i = 0; i < 8; i++){
        //clr[1] = i;               //�e�X�g�@���̈ʒu���Ƒ��M�����O�ɂɏ����������Ă��܂��f�[�^��������̂Œ���
        while(I2C1_IsBusy());
        I2C1_Write(OLED_address, clr, 129); //8page
        while(I2C1_IsBusy());   //�������݂��I���Ȃ������Ƀ��[�v�̐擪�ɋA��Ȃ��悤��
    }  
    return;
}


void putch_OLED(uint8_t c){
    //printf�Ŏg�p����putch�̒�` OLED
    //UART��putch����Ă΂��
    //���䕶���̏��O
    if (c == 0x0a){     //\n���s���A
        return;
    }
    
    if (baikaku == 1){
        chr57D(c);
    }else{
        chr57(c);
    }
}


void locate(uint8_t x, uint8_t y){
    //�P�ʂ�1����
    if (baikaku == 1){
        //�c�{�p6x16
        locate6x16(x,y);
    }else{
        //�W��6x8
        locate6x8(x,y);
    }
}
    

void locate6x8(uint8_t x, uint8_t y){    
    uint8_t  h4bit, l4bit, page;
    //x:0~21, y:0~7
    if (x <= 0){x = 0;}
    if (x > 21){x = 21;}
    if (y <= 0){y = 0;}
    if (y > 7){y = 7;}
    
    x = x * 6;              //�����̕�6�h�b�g
    //�R�����ʒu�@���4�r�b�g,����4�r�b�g�ɕ����āA2�R�}���h�ő��M
    l4bit = x & 0x0F;
    //���ʃA�h���X�Z�b�g�R�}���h�@0b0000xxxx
    x = x >> 4;
    h4bit = 0x10 + x;
    //��ʃA�h���X�Z�b�g�R�}���h�@0b0001xxxx

    page = 0xB0 + y;
    //0b10110xxx  �y�[�W 0~7

    uint8_t len = 6;
    uint8_t data[6] = {
    0x00,               //Co=0, D/C=0
    0x20, 0x02,         //set Page addressing mode
    page,               //set Page address
    l4bit,              //set Column addressL
    h4bit               //set Column addressH
    };
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, data, len);
    while(I2C1_IsBusy());
}
    

void locate6x16(uint8_t x, uint8_t y){
    uint8_t  start_column, end_column, start_page, end_page;
    //�c�{�p�@x:0~21, y:0~3
    if (x <= 0){x = 0;}
    if (x > 21){x = 21;}
    if (y <= 0){y = 0;}
    if (y > 3){y = 3;}
    
    start_column = x * 6;
    end_column = 127;

    start_page = y * 2;
    end_page =  start_page + 1;
    uint8_t len = 9;
    uint8_t data[9] = {
    0x00,                               //Co=0, D/C=0
    0x20, 0x01,                         //set Vertical addressing mode
    0x21, start_column, end_column,     //set Column address
    0x22, start_page, end_page          //set Page address
    };
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, data, len);
    while(I2C1_IsBusy());
}    
    

void chr57(uint8_t c){
    //5x7�t�H���g��1�����\���֐�
    uint8_t     i, len = 7;
    uint8_t     da[7];
    da[0] = 0x40;   //VRAM�֏���
    for(i = 0; i < 5; i++){
        da[i + 1] = Font5x7[c][i];  //�t�H���g�f�[�^���
    }
    da[6] = 0x00;                   //����
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, da, len);
    while(I2C1_IsBusy());
}


//**** 128 x 32 OLED�p�̕\�� *******
void chr57D(uint8_t c){
    //�c�{�p�t�H���g(5x14)��1�����\��
    uint8_t i, len = 13;
    uint16_t dd;
    uint8_t data[13];
    data[0] = 0x40;                         //VRAM�֏�������
    for(i = 0; i < 5; i++){
        dd = bitmap2x(Font5x7[c][i]);
        data[i * 2 + 1] = dd & 0x00ff;
        data[i * 2 + 2] = dd >> 8;  
    }
    data[11] = 0x00;                        //���� 
    data[12] = 0x00;                        //����
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, data, len);
    while(I2C1_IsBusy());
}


uint16_t bitmap2x(uint8_t data){
    //�c�{�p�̂��߂̃r�b�g�v�Z
    //�������ς�
    uint16_t bai = 0;
    if (data & 0b00000001){bai = 0b0000000000000011;}
    if (data & 0b00000010){bai = bai | 0b0000000000001100;}
    if (data & 0b00000100){bai = bai | 0b0000000000110000;}
    if (data & 0b00001000){bai = bai | 0b0000000011000000;}
    if (data & 0b00010000){bai = bai | 0b0000001100000000;}
    if (data & 0b00100000){bai = bai | 0b0000110000000000;}
    if (data & 0b01000000){bai = bai | 0b0011000000000000;}
    if (data & 0b10000000){bai = bai | 0b1100000000000000;}

    return bai;
}

   