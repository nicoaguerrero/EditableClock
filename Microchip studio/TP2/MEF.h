#ifndef _MEF_H
#define _MEF_H

#include "Keypad.h"
#include "sEOS.h"
#include "Clock.h"

typedef enum{INIT,EAN,EME,EDI,EHO,EMI,ESE} enum_estados;void MEF_Actualizar(void);
void MEF_Inicializar(void);
void fINIT(void);
void fEAN(void);
void fEME(void);
void fEDI(void);
void fEHO(void);
void fEMI(void);
void fESE(void);

#endif