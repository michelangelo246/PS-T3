#ifndef DATA_H
#define DATA_H
#include "listapalestras.h"
#include "listaeventos.h"

struct data
{
	ListaEventos encaixadas;
	int dia_do_ano;
	
};

typedef struct data* Data;

Data Cria_Data(void);

void Destroi_Data(Data d);

#endif