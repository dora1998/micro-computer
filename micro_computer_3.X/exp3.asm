#include "p16F1829.inc"
    __CONFIG _CONFIG1, _FOSC_INTOSC & _WDTE_OFF & _MCLRE_OFF
    __CONFIG _CONFIG2, _PLLEN_ON & _LVP_OFF
RES_VECT    CODE	0x0000
       
CNTA	    EQU		H'20'
	    
	    MOVLW	D'100'	    ; C: 1
	    MOVWF	CNTA	    ; C: 1
	    CALL	NLOOP	    ; C: 2
	    GOTO	STP	    ; C: 2
NLOOP	    NOP			    ; C: 1
	    NOP			    ; C: 1
	    DECFSZ	CNTA,F	    ; C: 1(2)
	    GOTO	NLOOP	    ; C: 2
	    RETURN		    ; C: 2
	    
STP	    GOTO	STP	    ; C: 2
       
	    END


