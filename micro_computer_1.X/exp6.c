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
    OPTION_REG = 0b11011000;    // プリスケーラ x1
    
    int freq = 1000;
    int togglePerSec = freq * 2;    // freq[Hz]の矩形波を出すための切替回数
    int cyclePerSec = (1000000 / togglePerSec) / 32;
    char isPlaying = 1;     // 0:off, 1:on
    
    while(1) {
        PORTC = 0b00000000;
        for (int j = 0; j < togglePerSec; j++) {
            for (int i = 0; i < cyclePerSec; i++) {
                while(TMR0IF == 0){}
                TMR0IF = 0;
            }
        
            if (isPlaying == 1)
                PORTC = PORTC == 0b00000000 ? 0b00000100 : 0b00000000;     // 音 ON/OFFトグル
        }
        isPlaying = isPlaying == 0 ? 1 : 0;
    }
}
