#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"
#include <stdlib.h>
#include "listaeventos.h"
struct calendario
{
	Data dias[367];
};

typedef struct calendario* Calendario;

Calendario Cria_Calendario();

void Destroi_Calendario(Calendario c);

#endif