#include "persistencia_palestras.h"

ListaPalestras obter_ListaPalestras()
{
	FILE* fp = fopen("palestras.txt", "r");

	ListaPalestras header = Le_palestras(fp);
	Aponta_Inicio_ListaPalestras(header);
	TrataListaPalestras(header);
	Aponta_Inicio_ListaPalestras(header);
	return header;
		
return 0;

}