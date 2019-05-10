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
    OPTION_REG = 0b11010111;
    
    short led = 0;          // 0:OFF, 1:ON
    int cyclePerSec = 1000000 / 8192;
    while(1) {
        for (int i = 0; i < cyclePerSec; i++) {
            while(TMR0IF == 0){}
            TMR0IF = 0;
        }
        
        PORTC = led == 1 ? 0b00000100 : 0b00000000;     // LED OFF
        led = led == 1 ? 0 : 1;
    }
}