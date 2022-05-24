#ifndef KEYPAD_H
#define KEYPAD_H

#include <inttypes.h>
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

uint8_t KEYPAD_Scan(uint8_t *);
uint8_t RetornarTecla(void);
void KEYPAD_Actualizar(void);

#endif