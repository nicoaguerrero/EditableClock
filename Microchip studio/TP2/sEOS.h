#ifndef SEOS_H
#define SEOS_H

#include <inttypes.h>
#include "Clock.h"
#include "main.h"
#include "Keypad.h"
#include "MEF.h"
#include "lcd.h"

void sEOS_Planificador(void);
void sEOS_Despachador(void);
void sEOS_time1(time);
void sEOS_time2(time);
void sEOS_timeBlank(time, uint8_t[]);

#endif