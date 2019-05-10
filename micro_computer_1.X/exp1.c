#pragma config FOSC     = INTOSC    // 発振
#pragma config WDTE     = OFF       // WDT 無効
#pragma config MCLRE    = OFF
#pragma config PLLEN    = ON        // PLL 有効
#pragma config LVP      = OFF

#include <xc.h>

void main() {
    PORTC = 0b00000000;     // クリア
    OSCCON = 0b11110000;    // 動作クロック: 32MHz
    TRISC = 0b00000000;     // 全て出力モード
    ANSELC = 0b00000000;    // 全てデジタルモード
    
    PORTC = 0b00000100;     // RC2 だけHIGH
    while(1){}
}