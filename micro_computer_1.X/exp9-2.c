#pragma config FOSC     = INTOSC    // 発振
#pragma config WDTE     = OFF       // WDT 無効
#pragma config MCLRE    = OFF
#pragma config PLLEN    = ON        // PLL 有効
#pragma config LVP      = OFF

#include <xc.h>

#define SENSOR_MIN 50
#define SENSOR_MAX 150

void main() {
    OSCCON = 0b11110000;    // 内蔵クロックを32Mhzに設定
    ANSELC = 0x00;          // PORTCは全てデジタル設定
    TRISC = 0x00;           // PORTCは全て出力モード
    CCP1CON = 0b1100;       // CCP1をPWMモードに設定
                            // CCP1X, CCP1Tは共に0
    T2CON = 0b111;          // タイマ2の分周比を1:64に設定（この例では下位3ビットを指定しており、省略したビットには0が入る）
    PR2 = 0xff;             // タイマ2のカウンタと比較する値
    OPTION_REG = 0b11011000;
    
    ANSELA = 0b00000100;    // AN2(RA2)をアナログ入力に使用
    TRISA = 0b00000111;     // RA2を入力へ、RA1,RA0も入力にしておく
    ANSELB = 0b00000000;
    TRISB = 0b10000000;     // RB7をデジタル入力へ
    ADCON0 = 0b00001011;
    ADCON1 = 0b00110000;
    
    CCPR1L = 0;
    
    // 16us以上待つ
    TMR0IF = 0;
    while(TMR0IF == 0){}
    TMR0IF = 0;
    
    int mode = 1;      // -1:OFF, 1:ON
    while(1) {
        if (RB7 == 0) {
            while(RB7 == 0) {}
            mode *= -1;
        }
        if (mode == 1) {
            ADGO = 1;
            while(ADGO==1) {}
            int led = (int)(255 * (ADRESH - SENSOR_MIN) * 1.0f / (SENSOR_MAX - SENSOR_MIN));
            if (led > 255) led = 255;
            if (led < 0) led = 0;
            CCPR1L = 255 - led;
        } else {
            CCPR1L = 0;
        }
    }
}



