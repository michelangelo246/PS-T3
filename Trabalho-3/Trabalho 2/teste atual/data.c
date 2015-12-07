#include "data.h"

Data Cria_Data()
{
    return malloc(sizeof(struct data));
}

void Destroi_Data(Data d)
{
    free(d);
}