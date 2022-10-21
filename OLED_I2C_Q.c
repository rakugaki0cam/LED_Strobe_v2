/*
 *File:   OLED_I2C_2.c
 *
 * 	Graphic OLED モジュール
 *    I2C SSD1306
 *
 *  PIC18F27Q43
 * 
 * 履歴
 * 2022.10.09   MoMoni_CAN_26K83よりPIC18F27Q43へ移植
 *              ノンブロッキングのため、続けてI2C1_Write()すると、busyにて戻ってきてしまう。
 *              送る前にI2C1_IsBusy()でフリーになるまで待つ。
 *              送信完了する前にデータをいじってしまうと正しく表示されない。
 *              とりあえず完了まで待たせる。
 * 2022.10.10   UARTのputchから呼ばれる。\n制御文字を除外
 * 
 * 
 * 
 * 
 */

#include    "OLED_I2C_Q.h"

#define     contrast    30   //127だと露出オーバーISO400　f2.8 1/1.6　60でもややオーバー

//ハードの選択
//#define     DISPLAYHEIGHT   64      //128x64 OLED
#define     DISPLAYHEIGHT   32      //128x32 OLED
//文字の大きさ(行数)
bool        baikaku = 0;            //縦倍角　128x32 OLEDの時は表示2行になる


void OLED_init(void){
    //OLEDの初期化
    i2c_host_error_t err;
    uint8_t da[10] = {
        0x00,           // Control byte bit7:Co=0, bit6:Data/Command#=0[command]
                        // Co=0 とすると以後連続して1バイトずつ送れる
                        // Co=1 とすると1バイト送る毎にControl byte を入れる必要がある
        0x81, contrast, // Set contrast
        0x8d,           // Set charge pump
#if DISPLAYHEIGHT == 32
        //128x32 OLED
        0xa8, 31,       //set MUXratio=32   
        0xda, 0x02,     //set COMpin 128x32用  {重要}
#endif
#if DISPLAYHEIGHT == 64  
    //128x64 OLED
        0xa8, 63,       //set MUXratio=64
        0xda, 0x12,     //set COMpin default
#endif    
        0x14,           // Enable charge pump
        0xaf            // Display ON
    };                  // その他の初期設定値はデフォルト
                        
    /*
    //2.24inch用
    OLED_reset_SetLow();
    __delay_ms(20);
    OLED_reset_SetHigh();
    __delay_ms(200);
    */
    
    err = I2C1_ErrorGet();
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, da, 10);
    while(I2C1_IsBusy());   //書き込み処理が終わらないうちにデータを触らせないように待ちとする
    
    return;
}


void OLED_clr(void) {
    // OLED 画面消去
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

    clr[0] = 0x40;                  //Control byte bit7:Co=0, bit6:Data/Command#=1[data VRAMへ書込]
    for(i = 1; i <= 128; i++){      // 128column
        clr[i] = 0x00;              // clear
    }
    
    for(i = 0; i < 8; i++){
        //clr[1] = i;               //テスト　この位置だと送信完了前にに書き換えられてしまいデータが化けるので注意
        while(I2C1_IsBusy());
        I2C1_Write(OLED_address, clr, 129); //8page
        while(I2C1_IsBusy());   //書き込みが終わらないうちにループの先頭に帰らないように
    }  
    return;
}


void putch_OLED(uint8_t c){
    //printfで使用するputchの定義 OLED
    //UARTのputchから呼ばれる
    //制御文字の除外
    if (c == 0x0a){     //\n改行復帰
        return;
    }
    
    if (baikaku == 1){
        chr57D(c);
    }else{
        chr57(c);
    }
}


void locate(uint8_t x, uint8_t y){
    //単位は1文字
    if (baikaku == 1){
        //縦倍角6x16
        locate6x16(x,y);
    }else{
        //標準6x8
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
    
    x = x * 6;              //文字の幅6ドット
    //コラム位置　上位4ビット,下位4ビットに分けて、2コマンドで送信
    l4bit = x & 0x0F;
    //下位アドレスセットコマンド　0b0000xxxx
    x = x >> 4;
    h4bit = 0x10 + x;
    //上位アドレスセットコマンド　0b0001xxxx

    page = 0xB0 + y;
    //0b10110xxx  ページ 0~7

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
    //縦倍角　x:0~21, y:0~3
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
    //5x7フォントの1文字表示関数
    uint8_t     i, len = 7;
    uint8_t     da[7];
    da[0] = 0x40;   //VRAMへ書込
    for(i = 0; i < 5; i++){
        da[i + 1] = Font5x7[c][i];  //フォントデータ代入
    }
    da[6] = 0x00;                   //字間
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, da, len);
    while(I2C1_IsBusy());
}


//**** 128 x 32 OLED用の表示 *******
void chr57D(uint8_t c){
    //縦倍角フォント(5x14)の1文字表示
    uint8_t i, len = 13;
    uint16_t dd;
    uint8_t data[13];
    data[0] = 0x40;                         //VRAMへ書き込み
    for(i = 0; i < 5; i++){
        dd = bitmap2x(Font5x7[c][i]);
        data[i * 2 + 1] = dd & 0x00ff;
        data[i * 2 + 2] = dd >> 8;  
    }
    data[11] = 0x00;                        //字間 
    data[12] = 0x00;                        //字間
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, data, len);
    while(I2C1_IsBusy());
}


uint16_t bitmap2x(uint8_t data){
    //縦倍角のためのビット計算
    //高速化済み
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

   