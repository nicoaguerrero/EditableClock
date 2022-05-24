#include <avr/interrupt.h>
#include <avr/io.h>
#include "sEOS.h"
#include "Clock.h"

static uint8_t counter = 0;

void init(void)
{
	DDRC = 0xFF;
	TCCR0A = (1 << WGM01);
	OCR0A = 156; //0.01 sec
	TIMSK0 = (1 << OCIE0A);
	TCCR0B = (1 << CS02) | (1 << CS00); // prescaler 1024
	sei();
}


ISR(TIMER0_COMPA_vect)
{
	counter++;
	if(counter > 100){
		if (++t.second==60)
		{
			t.second=0;
			if (++t.minute==60)
			{
				t.minute=0;
				if (++t.hour==24)
				{
					t.hour=0;
					if (++t.date==32)
					{
						t.month++;
						t.date=1;
					}
					else if (t.date==31)
					{
						if ((t.month==4) || (t.month==6) || (t.month==9) || (t.month==11))
						{
							t.month++;
							t.date=1;
						}
					}
					else if (t.date==30)
					{
						if(t.month==2)
						{
							t.month++;
							t.date=1;
						}
					}
					else if (t.date==29)
					{
						if((t.month==2) && (not_leap()))
						{
							t.month++;
							t.date=1;
						}
					}
					if (t.month==13)
					{
						t.month=1;
						t.year++;
					}
				}
			}
		}

		counter = 0;
	}
	sEOS_Planificador();
}

char not_leap(void)      //check for leap year
{
	if (!(t.year%100))
	{
		return (char)(t.year%400);
	}
	else
	{
		return (char)(t.year%4);
	}
}

time obtenerTime(void){
	return t;
}

void setearTime(time newTime){
	t=newTime;
}