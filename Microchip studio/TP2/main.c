#include "main.h"

uint8_t key;

int main(void)
{
	init();
	LCDinit();
	MEF_Inicializar();
	sEOS_time1(t);
	while(1)
	{
		sEOS_Despachador();
	}
}


void LCD_Actualizar(time t){

	LCDGotoXY(4,1);
	LCDescribeDato(t.date,2);
	LCDsendChar('/');
	LCDescribeDato(t.month,2);
	LCDsendChar('/');
	LCDescribeDato(t.year,2);
	LCDGotoXY(4,0);
	LCDescribeDato(t.hour,2);
	LCDsendChar(':');
	LCDescribeDato(t.minute,2);
	LCDsendChar(':');
	LCDescribeDato(t.second,2);	
}
 

