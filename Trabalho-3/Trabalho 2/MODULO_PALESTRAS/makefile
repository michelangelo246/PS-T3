programa: palestra.o lista_palestras.o palestras_leitura.o persistencia_palestras.o tratapalestras.o
	splint *.c -weak +infloops +compdef +sysdirerrors -preproc ->relatorio_splint_palestras.txt

palestra.o: palestra.c palestra.h
	gcc -c palestra.c
lista_palestras.o: 
	gcc -c lista_palestras.c
palestras_leitura.o: 
	gcc -c palestras_leitura.c
persistencia_palestras.o: 
	gcc -c persistencia_palestras.c
tratapalestras.o:
	gcc -c tratapalestras.c


