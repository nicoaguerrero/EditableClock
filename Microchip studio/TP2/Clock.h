#ifndef CLOCK_H
#define CLOCK_H

#include <inttypes.h>

typedef struct{
	unsigned char second ;
	unsigned char minute;
	unsigned char hour;
	unsigned char date;
	unsigned char month;
	unsigned char year;
}time;

static volatile time t={59,59,23,31,12,21};

void init(void);
char not_leap(void);
time obtenerTime(void);
void setearTime(time);

#endif