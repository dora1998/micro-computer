#pragma config FOSC     = INTOSC    // 発振
#pragma config WDTE     = OFF       // WDT 無効
#pragma config MCLRE    = OFF
#pragma config PLLEN    = ON        // PLL 有効
#pragma config LVP      = OFF

#include <xc.h>

void main() {
    OSCCON = 0b11110000;    // 内蔵クロックを32Mhzに設定
    ANSELC = 0x00;          // PORTCは全てデジタル設定
    TRISC = 0x00;           // PORTCは全て出力モード
    CCP1CON = 0b1100;       // CCP1をPWMモードに設定
                            // CCP1X, CCP1Tは共に0
    T2CON = 0b111;          // タイマ2の分周比を1:64に設定（この例では下位3ビットを指定しており、省略したビットには0が入る）
    PR2 = 0xff;             // タイマ2のカウンタと比較する値
    OPTION_REG = 0b11011000;
    
    CCPR1L = 20;
    int cycleTenMSec = 10000 / 32;
    int d = 1;
    while(1) {
        CCPR1L += 1 * d;           // デューティサイクルを設定
        if (CCPR1L == 0 || CCPR1L == 255) d *= -1;
        for (int i = 0; i < cycleTenMSec; i++) {
            while(TMR0IF == 0){}
            TMR0IF = 0;
        }
    }
}
