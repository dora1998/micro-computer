#pragma config FOSC     = INTOSC    // 発振
#pragma config WDTE     = OFF       // WDT 無効
#pragma config MCLRE    = OFF
#pragma config PLLEN    = ON        // PLL 有効
#pragma config LVP      = OFF

#include <xc.h>

#define FREQ_C 262
#define FREQ_D 294
#define FREQ_E 330
#define FREQ_F 349
#define FREQ_G 392
#define FREQ_A 440
#define FREQ_B 494

void sleep(int msec) {
    OPTION_REG = 0b11010111;    // プリスケーラ x256
    int cycle = (int)(msec / 8.192);
    for (int i = 0; i < cycle; i++) {
        while(TMR0IF == 0){}
        TMR0IF = 0;
    }
}

void tone(int msec, int freq) {
    OPTION_REG = 0b11011000;    // プリスケーラ x1
    int cycleSound = (1000000 / (freq * 2)) / 32;  // freq[Hz]の矩形波を出すための切替回数
    int cycleEntire = freq * 2;
    
    PORTC = 0b00000000;
    for (int j = 0; j < cycleEntire; j++) {
        for (int i = 0; i < cycleSound; i++) {
            while(TMR0IF == 0){}
            TMR0IF = 0;
        }

        PORTC = PORTC == 0b00000000 ? 0b00000100 : 0b00000000;     // 音 ON/OFFトグル
    }
}

void main() {
    PORTC = 0b00000000;     // クリア
    OSCCON = 0b11110000;    // 動作クロック: 32MHz
    TRISC = 0b00000000;     // 全て出力モード
    ANSELC = 0b00000000;    // 全てデジタルモード
    OPTION_REG = 0b11011000;    // プリスケーラ x1
    
    tone(500, FREQ_C);
    tone(500, FREQ_D);
    tone(500, FREQ_E);
    tone(500, FREQ_F);
    tone(500, FREQ_E);
    tone(500, FREQ_D);
    tone(500, FREQ_C);
    sleep(1000);
    
    tone(500, FREQ_E);
    tone(500, FREQ_F);
    tone(500, FREQ_G);
    tone(500, FREQ_A);
    tone(500, FREQ_G);
    tone(500, FREQ_F);
    tone(500, FREQ_E);
    sleep(1000);
    
    tone(500, FREQ_C);
    sleep(1000);
    tone(500, FREQ_C);
    sleep(1000);
    tone(500, FREQ_C);
    sleep(1000);
    tone(500, FREQ_C);
    sleep(1000);
    
    tone(250, FREQ_C);
    tone(250, FREQ_C);
    tone(250, FREQ_D);
    tone(250, FREQ_D);
    tone(250, FREQ_E);
    tone(250, FREQ_E);
    tone(250, FREQ_F);
    tone(250, FREQ_F);
    tone(250, FREQ_E);
    tone(250, FREQ_E);
    tone(250, FREQ_D);
    tone(250, FREQ_D);
    tone(250, FREQ_C);
    tone(250, FREQ_C);
}

