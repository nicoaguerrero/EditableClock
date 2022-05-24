#include "Keypad.h"

const char keypad[4][4] = {
	{'2','3','1','A'},
	{'5','6','4','B'},
	{'8','9','7','C'},
	{'*','#','0','D'}
};

static uint8_t tecla;

uint8_t KEYPAD_Scan (uint8_t *key){
	uint8_t c;
	
	PORTB|= 0x19; //00011001 PB4,3,0 en salida
	PORTD|= 0x80; //10000000 D2,3,4,5 en entrada, RS en 1 -> cambiado a 0 por errores
	//DDRB|=(0x6); //00110
	for (c=0;c<4;c++)
	{
		DDRD&=~(0x3C); //00111100
		DDRD|=(0X20>>c); //00100000 Movimiento en columnas
		_delay_ms(1);
		if(!(PINB&(0x10))){ //00010000
			*key = keypad[0][c];
			return 1;
		}
		if(!(PINB&(0x08))){
			*key = keypad[1][c];
			return 1;
		}
		if(!(PINB&(0x1))){
			*key = keypad[2][c];
			return 1;
		}
		if(!(PIND&(0x80))){
			*key = keypad[3][c];
			return 1;
		}
		
	}
	return 0;
}

void KEYPAD_Actualizar(void){ 
	uint8_t key=' '; 
	if(KEYPAD_Scan(&key)){  
		tecla=key;  
	} 
	else tecla=0;
}

uint8_t RetornarTecla(void){
	return tecla;
}