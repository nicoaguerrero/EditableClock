#include "sEOS.h"

#define INIT_KEYPAD 20
#define INIT_MEF 10
#define INIT_LCD 1
#define INIT_BLANCO 100

static int8_t contKeypad=19;
static int8_t contMEF=9;
static int8_t contLCD=0;
static int8_t contBlanco=99;

static uint8_t FlagKeypad=0;
static uint8_t FlagMEF=0;
static uint8_t FlagLCD=0;
static uint8_t FlagBlanco=0;

static time tiempo1,tiempo2,tiempoBlanco;
static uint8_t cond=1;

void sEOS_Planificador(void){ 
	if(++contMEF==INIT_MEF){  
		FlagMEF=1;  
		contMEF=0;  
	}
	if(++contLCD==INIT_LCD){
		FlagLCD=1;
		contLCD=0;
	}
	if(++contKeypad==INIT_KEYPAD){
		FlagKeypad=1;
		contKeypad=0;
	}
	if(++contBlanco==INIT_BLANCO){
		FlagBlanco=1;
		contBlanco=0;
	}
}

void sEOS_Despachador(void){ 
	if(FlagKeypad==1){  
		KEYPAD_Actualizar();  
		FlagKeypad=0;  
	}
	if(FlagMEF==1){  
		MEF_Actualizar();  
		FlagMEF=0;  
	}
	if((FlagLCD==1)&(cond==1)){
		LCD_Actualizar(tiempo1);
		FlagLCD=0;
		tiempo1=obtenerTime();
	}else if((FlagLCD==1)&(cond==0)){
		LCD_Actualizar(tiempo2);
		FlagLCD=0;
		cond = 2;
	}
	if((FlagBlanco==1)&(cond==2)){
		LCD_Actualizar(tiempoBlanco);
		FlagBlanco=0;
		cond = 0;
	}
}



void sEOS_time1(time t){
	tiempo1=t;
	cond=1;
}

void sEOS_time2(time t){
	tiempo2=t;
	cond=0;
}

void sEOS_timeBlank(time t, uint8_t b[]){
	for (int i = 0; i<6;i++)
	{
		if((i==0) &(b[i]==' ')){
			LCDGotoXY(10,1);
			LCDsendChar(b[i]);
			LCDsendChar(b[i]);
			b[i]='0';
		}else if((i==1) &(b[i]==' ')){
				LCDGotoXY(7,1);
				LCDsendChar(b[i]);
				LCDsendChar(b[i]);
				b[i]='0';
			}else if((i==2) &(b[i]==' ')){
						LCDGotoXY(4,1);
						LCDsendChar(b[i]);
						LCDsendChar(b[i]);
						b[i]='0';
				}else if((i==3) &(b[i]==' ')){
						LCDGotoXY(4,0);
						LCDsendChar(b[i]);
						LCDsendChar(b[i]);
						b[i]='0';
						}else if((i==4) &(b[i]==' ')){
								LCDGotoXY(7,0);
								LCDsendChar(b[i]);
								LCDsendChar(b[i]);
								b[i]='0';
							}else if((i==5) &(b[i]==' ')){
									LCDGotoXY(10,0);
									LCDsendChar(b[i]);
									LCDsendChar(b[i]);
									b[i]='0';
									}
	}
	tiempoBlanco=t;
}