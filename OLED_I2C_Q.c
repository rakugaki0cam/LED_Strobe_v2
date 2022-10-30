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
 * 2022.10.29   12x16ドットフォントを追加
 * 
 * 
 * 
 * OCRで読み込みやすい大きなフォントに変更したい
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


fontsize_t     font_size = FONT5X7;


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
    switch(font_size){
        case FONT5X7:
            chr57(c);
            break;
        case FONT5X14:
            chr57D(c);
            break;   
        case FONT12:  
            chr12(c);
            break;   
    }  
}


void locate(uint8_t x, uint8_t y){
    //単位は1文字
    switch(font_size){
        case FONT5X7:
            locate6x8(x,y);
            break;
        case FONT5X14:
            locate6x16(x,y);
            break;   
        case FONT12:  
            locate12x16(x,y);
            break;   
    }  
}
    

void locate6x8(uint8_t x, uint8_t y){    
    uint8_t  h4bit, l4bit, page;
    //x:0~20
    if (x <= 0){x = 0;}
    if (x > 20){x = 20;}
    if (y <= 0){y = 0;}
#if DISPLAYHEIGHT == 64      
    if (y > 7){y = 7;}      //128x64 OLED y:0~7
#else
    if (y > 3){y = 3;}      //128x32 OLED y:0~3
#endif
    
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
    //縦倍角　x:0~20
    if (x <= 0){x = 0;}
    if (x > 20){x = 20;}
    if (y <= 0){y = 0;}
#if DISPLAYHEIGHT == 64      
    if (y > 7){y = 7;}      //128x64 OLED y:0~7
#else
    if (y > 3){y = 3;}      //128x32 OLED y:0~3
#endif
    
    start_column = x * 6;
    end_column = 127;

    start_page = y * 2;     //pageは縦8ドットー0～7ページで64ドット
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
    

void locate12x16(uint8_t x, uint8_t y){
    uint8_t  start_column, end_column, start_page, end_page;
    //12x16　x:0~19
    if (x <= 0){x = 0;}
    if (x > 19){x = 19;}
    if (y <= 0){y = 0;}
#if DISPLAYHEIGHT == 64      
    if (y > 3){y = 3;}      //128x64 OLED y:0~3
#else
    if (y > 1){y = 1;}      //128x32 OLED y:0~1
#endif
    start_column = x * 12;
    end_column = 127;

    start_page = y * 2;     //pageは縦8ドットー0～7ページで64ドット
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
    
#define     LEN5X7      7       //フォントデータバイト数+1
    uint8_t     i;
    uint8_t     da[LEN5X7];
    
    da[0] = 0x40;               //VRAMへ書込コマンド
    for(i = 0; i < 5; i++){
        da[i + 1] = Font5x7[c][i];  //フォントデータ代入
    }
    da[6] = 0x00;                   //字間
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, da, LEN5X7);
    while(I2C1_IsBusy());
}


//**** 128 x 32 OLED用の表示 *******
void chr57D(uint8_t c){
    //縦倍角フォント(5x14)の1文字表示
    
#define     LEN5X14     13      //フォントデータバイト数+1
    uint8_t i;
    uint16_t dd;
    uint8_t data[LEN5X14];
    
    data[0] = 0x40;             //VRAMへ書き込みコマンド
    for(i = 0; i < 5; i++){
        dd = bitmap2x(Font5x7[c][i]);
        data[i * 2 + 1] = dd & 0x00ff;
        data[i * 2 + 2] = dd >> 8;  
    }
    data[11] = 0x00;                        //字間 
    data[12] = 0x00;                        //字間
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, data, LEN5X14);
    while(I2C1_IsBusy());
}


uint16_t bitmap2x(uint8_t data){
    //縦倍角のためのビット計算
    //8ビットデータ→16ビットデータ
    //高速化済み
    uint16_t bai = 0;
    if (data & 0b00000001){bai =       0b0000000000000011;}
    if (data & 0b00000010){bai = bai | 0b0000000000001100;}
    if (data & 0b00000100){bai = bai | 0b0000000000110000;}
    if (data & 0b00001000){bai = bai | 0b0000000011000000;}
    if (data & 0b00010000){bai = bai | 0b0000001100000000;}
    if (data & 0b00100000){bai = bai | 0b0000110000000000;}
    if (data & 0b01000000){bai = bai | 0b0011000000000000;}
    if (data & 0b10000000){bai = bai | 0b1100000000000000;}

    return bai;
}


void chr12(uint8_t c){
    // 12x16dotフォントの1文字表示関数
    
#define     LEN12       25  //フォントデータバイト数+1
    uint8_t i;    
    uint8_t data[LEN12];
    
    c = ascii_font12(c);    //アスキーコード換算
    
    data[0] = 0x40;         //VRAMへ書き込みコマンド
    
    for(i = 0; i < 12; i++){
        data[i * 2 + 1] = font12[c][i];
        data[i * 2 + 2] = font12[c][i + 12];  
    } 
    
    while(I2C1_IsBusy());
    I2C1_Write(OLED_address, data, LEN12);
    while(I2C1_IsBusy());

}

uint8_t ascii_font12(uint8_t ascii_code){
    //フォントデータがまばらなのでコードを変換
    uint8_t     font_code;
    
    if ((ascii_code >= 0x30) && (ascii_code <= 0x39)){
        font_code = ascii_code - 0x30;
        return font_code;
    }
    
    switch(ascii_code){
        case 0x30 ... 0x39:
            //なぜか0x30しかとおらないCコンパイラのバグ???
            break;
        case 0x2e:
        case 0x2f:
            font_code = ascii_code - 0x2e + 0x0b;
            break;
        case 0x48:
            font_code = 0x0d;
            break;
        case 0x4d:
            font_code = 0x0e;
            break;
        case 0x6b:
            font_code = 0x0f;
            break;
        case 0x6d:
            font_code = 0x10;
            break;
        case 0x73:
            font_code = 0x11;
            break;
        case 0x75:
            font_code = 0x12;
            break;
        case 0x7a:
            font_code = 0x13;
            break;
        default:        //フォントデータ無し
            font_code = 0x0a;
            break;
    }
    
    return font_code;
}