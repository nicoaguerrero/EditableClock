#include "MEF.h"

static void aplicarTiempo(time);

void (*MEF_funciones[])(void) = {fINIT,fEAN,fEME,fEDI,fEHO,fEMI,fESE};
	
static enum_estados estado;
static uint8_t flag = 0;
static time ti;
static uint8_t blanco[6]={0};

	
void MEF_Inicializar(void){
	estado = INIT;
}

void MEF_Actualizar(void){
	if (flag)
		flag=0;
	else
		flag=1;
	(*MEF_funciones[estado])();
}

void fINIT(void)
{
	if(flag==1){
		uint8_t tecla = RetornarTecla();
		if(tecla == 'A'){ 
			ti=obtenerTime();
			sEOS_time2(ti);
			estado = EAN;
		}
	}
}

void fEAN(void){
	if(flag==1){
		blanco[0]=' ';
		sEOS_timeBlank(ti,blanco);
		uint8_t tecla = RetornarTecla();
		switch(tecla){
			case 'A':
				estado = EME;
				break;
			case 'B':
				ti.year++;
				if(ti.year==100){
					ti.year=0;
				}
				sEOS_time2(ti);
				break;
			case 'C':
				ti.year--;
				if(ti.year==255){
					ti.year=99;
				}
				sEOS_time2(ti);
				break;
			case 'D':
				ti=obtenerTime();
				sEOS_time1(ti);
				estado = INIT;
				break;
		}
	}
}

void fEME(void){
	if(flag==1){
		blanco[1]=' ';
		sEOS_timeBlank(ti,blanco);
		uint8_t tecla = RetornarTecla();
		switch(tecla){
			case 'A':
			estado = EDI;
			break;
			case 'B':
			ti.month++;
			if(ti.month==13){
				ti.month=1;
			}
			if((ti.month==2)&(ti.date>29)){
				ti.date=1;
			}
			if( ((ti.month==4) || (ti.month==6) || (ti.month==9) || (ti.month==11))){
				if(ti.date>30){
					ti.date=1;
				}
			}
			sEOS_time2(ti);
			break;
			case 'C':
			ti.month--;
			if(ti.month==0){
				ti.month=12;
			}
			if((ti.month==2)&(ti.date>29)){
				ti.date=1;
			}
			if( ((ti.month==4) || (ti.month==6) || (ti.month==9) || (ti.month==11))){
				if(ti.date>30){
					ti.date=1;
				}
			}
			sEOS_time2(ti);
			break;
			case 'D':
			ti=obtenerTime();
			sEOS_time1(ti);
			estado = INIT;
			break;
		}
	}
}
	
void fEDI(void){
	if(flag==1){
		blanco[2]=' ';
		sEOS_timeBlank(ti,blanco);
		uint8_t tecla = RetornarTecla();
		switch(tecla){
			case 'A':
			estado = EHO;
			break;
			case 'B':
			ti.date++;
			if((ti.month==2)&(ti.date==30)){
				ti.date=1;
			}
			if( ((ti.month==4) || (ti.month==6) || (ti.month==9) || (ti.month==11))){
				if(ti.date==31){
					ti.date=1;
				}
			}else if(ti.date==32){
				ti.date=1;
			}
			sEOS_time2(ti);
			break;
			case 'C':
			ti.date--;
			if((ti.month==2)&(ti.date==0)){
				ti.date=29;
			}
				if( ((ti.month==4) || (ti.month==6) || (ti.month==9) || (ti.month==11))){
					if(ti.date==0){
						ti.date=30;
					}
					}else if(ti.date==0){
					ti.date=31;
				}
			sEOS_time2(ti);
			break;
			case 'D':
			ti=obtenerTime();
			sEOS_time1(ti);
			estado = INIT;
			break;
		}
	}
}

void fEHO(void){
	if(flag==1){
		blanco[3]=' ';
		sEOS_timeBlank(ti,blanco);
		uint8_t tecla = RetornarTecla();
		switch(tecla){
			case 'A':
			estado = EMI;
			break;
			case 'B':
			ti.hour++;
			if(ti.hour==24){
				ti.hour=0;
			}
			sEOS_time2(ti);
			break;
			case 'C':
			ti.hour--;
			if(ti.hour==255){
				ti.hour=23;
			}
			sEOS_time2(ti);
			break;
			case 'D':
			ti=obtenerTime();
			sEOS_time1(ti);
			estado = INIT;
			break;
		}
	}
}

void fEMI(void){
	if(flag==1){
		blanco[4]=' ';
		sEOS_timeBlank(ti,blanco);
		uint8_t tecla = RetornarTecla();
		switch(tecla){
			case 'A':
			estado = ESE;
			break;
			case 'B':
			ti.minute++;
			if(ti.minute==60){
				ti.minute=0;
			}
			sEOS_time2(ti);		
			break;
			case 'C':
			ti.minute--;
			if(ti.minute==255){
				ti.minute=59;
			}
			sEOS_time2(ti);
			break;
			case 'D':
			ti=obtenerTime();
			sEOS_time1(ti);
			estado = INIT;
			break;
		}
	}
}

void fESE(void){
	if(flag==1){
		blanco[5]=' ';
		sEOS_timeBlank(ti,blanco);
		uint8_t tecla = RetornarTecla();
		switch(tecla){
			case 'A':
			aplicarTiempo(ti);
			sEOS_time1(ti);
			estado = INIT;
			break;
			case 'B':
			ti.second++;
			if(ti.second==60){
				ti.second=0;
			}
			sEOS_time2(ti);
			break;
			case 'C':
			ti.second--;
			if(ti.second==255){
				ti.second=59;
			}
			sEOS_time2(ti);
			break;
			case 'D':
			ti=obtenerTime();
			sEOS_time1(ti);
			estado = INIT;
			break;
		}
	}
}



static void aplicarTiempo(time newTime){
	if(newTime.hour<25){
		if(newTime.minute<60){
			if(newTime.second<60){
				if(newTime.month<13){
					if(newTime.date<32){
						if ((newTime.month==4) || (newTime.month==6) || (newTime.month==9) || (newTime.month==11)){
							if(newTime.date<31) setearTime(newTime);
						}else if(newTime.month==2){
							if(not_leap()){
								if(newTime.date<29) setearTime(newTime);
							}else if(newTime.date<30) setearTime(newTime);
						}else setearTime(newTime);
					}
				}
			}
		}
	}
}
