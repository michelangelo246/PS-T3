#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "leitura.c"
#include "tratadados.c"
#include "controletempo.c"
#include "calendario.c"
#include "listapalestrantes.c"
#include "listapalestras.c"
#include "palestras.h"
#include "palestrantes.h"
//#include "listadisponibilidade.c"



///DEFINIÇÕES_DAS_SUITES
    void adicionar_testes(void);
    
    /* _SUITE_CALENDARIO_ */
        /*Testes da funcao "Cria_Grade"*/
            void Cria_Grade_1(void);
            /*Testa se a funcao realmente cria 48 nós de horario*/
        
        /*Testes da funcao "Cria_Calendario"*/
            void Cria_Calendario_2(void);
            /*Testa se a função calendario cria uma grade horaria com 48 nós*/
        
    /* _END_SUITE_ */
    
    /* _SUITE_LEITURA_ */
        /*Testes da funcao "Le_palestrantes"*/
            void Le_palestrantes_1(void);
            /*Testa se a alocação das disponibilidades é feita corretamente para cada palestrante*/
            
            void Le_palestrantes_2(void);
            
    /* _END_SUITE_ */

    
    /* _SUITE_LISTA_ */
        /*Testes da funcao x*/
            void Cria_ListaPalestrantes_1(void);
            
            void Cria_ListaPalestras_1(void);
            
            void Cria_ListaDisponibilidade_1(void);
            
            void Limpa_ListaPalestras_1(void);
            
            void Limpa_ListaPalestrantes_1(void);
            
            void Limpa_ListaDisponibilidade_1(void);
            
            void Info_Corrente_ListaPalestras_1(void);
        
    /* _END_SUITE_ */

        
///DEFINIÇÕES_DAS_SUITES_END


///IMPLEMENTAÇÕES_DAS_SUITES
    
    /* _SUITE_CALENDARIO_ */
        /*Testes da funcao "Cria_Grade"*/
        
            void Cria_Grade_1(void)
            {
                tipo_tempo *teste;
                int pass=1,i;
                
                teste=Cria_Grade();
                for(i=0;i<47;i++)
                {
                    if(teste->boleano!=0)
                    {
                        pass=0;
                        break;
                    }
                    teste=teste->prox;
                }
                CU_ASSERT_TRUE(pass==1);
            }
            
        /*Testes da função "Cria_Calendario"*/
        
            void Cria_Calendario_2(void)
            {
                ListaPalestras *p1;
                NodoPalestras *n1_palestras,*n2_palestras;
                Palestra *n1_palestras_p,*n2_palestras_p;
            
                p1=(ListaPalestras *)malloc(sizeof(ListaPalestras));
                n1_palestras = (NodoPalestras *)malloc(sizeof(NodoPalestras));
                n2_palestras = (NodoPalestras *)malloc(sizeof(NodoPalestras));
                n1_palestras_p = (Palestra *)malloc(sizeof(Palestra));
                n2_palestras_p = (Palestra *)malloc(sizeof(Palestra));
            
                n1_palestras->pprev = NULL;
                n1_palestras->pnext = n2_palestras;
                n1_palestras->p = n1_palestras_p;
            
                n2_palestras->pnext = NULL;
                n2_palestras->pprev = n1_palestras;
                n2_palestras->p = n2_palestras_p;
            
                strcpy(n1_palestras_p->nome_palestra,"Palestra1");
                strcpy(n2_palestras_p->nome_palestra,"Palestra2");
                strcpy(n1_palestras_p->responsavel,"Palestrante1");
                strcpy(n2_palestras_p->responsavel,"Palestrante2");
            
            
                n1_palestras_p->duracao_tratada = 60;
                n2_palestras_p->duracao_tratada = 60;
            
                p1->first = p1->current = n1_palestras;
                p1->last = n2_palestras;
            
            
                FILE *arq = fopen("entrada1.txt","r");
                ListaPalestrantes *teste_palestrantes = Le_palestrantes(arq);;
                ListaPalestras *teste_palestras = p1;
                tipo_calendario *teste_calendario,*aux_cal;
                tipo_agenda_palestrante *aux_pal;
                tipo_agendado *aux_agenda;
            
                teste_palestrantes->first->p->lista_disponibilidades->d->data = 366;
                teste_palestrantes->first->p->lista_disponibilidades->d->hora_inicio = 30;
                teste_palestrantes->first->p->lista_disponibilidades->d->hora_fim = 1380;
            
                teste_calendario = Cria_Calendario(teste_palestrantes, teste_palestras);
            
                aux_cal=teste_calendario;
                while(aux_cal)
                {
                    if(aux_cal->marcado == 1)
                    {
                        printf("agenda:\n");
                        aux_agenda=aux_cal->agenda;
                        while(aux_agenda)
                        {
                            printf("\n\%s\n\n",aux_agenda->nome_palestrante);
                            aux_pal = aux_agenda->palestras;
                            while(aux_pal)
                            {
                                printf("%s \n",aux_pal->nome_palestra);
                                printf("inicio: %d:%d \nfim: %d:%d\n",aux_pal->inicio_palestra/60, aux_pal->inicio_palestra%60,aux_pal->fim_palestra/60,aux_pal->fim_palestra%60);
                                aux_pal=aux_pal->prox;
                            }
                            aux_agenda = aux_agenda->prox;
                        }
                    }
                    if(aux_cal->prox)
                        aux_cal=aux_cal->prox;
                    else
                        break;
                }
            
            
            }
            
            
    /* _END_SUITE_ */
    
    /* _SUITE_LEITURA_ */
        /*Testes da funcao "Le_palestrantes"*/
        
            void Le_palestrantes_1(void)
            {
                FILE *arq = fopen("entrada1.txt","r");
                ListaPalestrantes *teste;
                NodoPalestrantes *aux;
                ListaDisponibilidade *aux2;
                
                teste = Le_palestrantes(arq);
                
                aux=teste->first;
                while(aux)
                {
                    aux2=aux->p->lista_disponibilidades;
                    while(aux2)
                    {
                        CU_ASSERT_TRUE(aux2!=NULL);
                        aux2 = aux2->pnext;
                    }
                    aux = aux->pnext;
                }
            }
            
            void Le_palestrantes_2(void)
            {
                FILE *arq = fopen("entrada1.txt","r");
                FILE *arq2 = fopen("entrada2.txt","r");
                int i=0,j=0;
                
                ListaPalestrantes *teste_palestrantes;
                NodoPalestrantes *aux;
                ListaDisponibilidade *aux2;
                tipo_calendario *teste_calendario,*aux_cal;
                tipo_agenda_palestrante *aux_pal;
                tipo_agendado *aux_agenda;
                
                teste_palestrantes = Le_palestrantes(arq);
                
                aux=teste_palestrantes->first;
                while(aux)
                {
                    aux2=aux->p->lista_disponibilidades;
                    i=0;
                    printf("\n\nNome: %s\n",aux->p->nome_palestrante);
                    while(aux2)
                    {
                        printf("%s",aux2->d->dado_bruto);
                        aux2 = aux2->pnext;
                        i++;
                    }
                    j++;
                    aux = aux->pnext;
                }
                getchar();
                
                
                //TrataListaPalestrantes(&teste_palestrantes);
                
                
                /*printf("\n\n***\tSaida: \t\t(impressao da lista de palestrantes tratada)");
                */
                aux=teste_palestrantes->first;
                while(aux)
                {
                    /*printf("\n\n## %s ##\n", aux->p->nome_palestrante);
                    printf(" DISPONIBILIDADES:");*/
                    aux2=aux->p->lista_disponibilidades;
                    i=0;
                    while(aux2)
                    {
                        printf("\n\n%s\n",aux->p->nome_palestrante);
                        printf("disponibilidade n.%d:\n",i+1);
                        printf(" dado_bruto: %s\n", aux2->d->dado_bruto);
                        printf(" data: %d\n",aux2->d->data);
                        printf(" hora_inicio: %d\n",aux2->d->hora_inicio);
                        printf(" hora_fim: %d\n",aux2->d->hora_fim);
                        aux2 = aux2->pnext;
                        i++;
                    }
                    aux = aux->pnext;
                }
                getchar();
                
                
                
                //teste_palestras = Le_palestras(arq2);
                //aux_estras = teste_palestras->first;
                
                /* ======================== PALESTRAS ======================== *
                printf("\n\n***\tSaida: \t\t(impressao da lista de palestras lida)");
                
                while(aux_estras)
                {
                    printf("\n\n## ---- ##\n");
                    
                    printf("\nNome da Palestra n.%d: %s", i+1, aux_estras->p->nome_palestra );
                    printf("\nResponsavel: %s\n", aux_estras->p->responsavel);
                    printf("\nTema: %s\n", aux_estras->p->tema);
                    printf("\nLocal: %s\n", aux_estras->p->local);
                    printf("\nDuracao Bruta: %s\n", aux_estras->p->duracao_bruta);
                    aux_estras = aux_estras->pnext;
                        i++;
                }
                
                getchar();
                
                TrataListaPalestras(&teste_palestras);
                aux_estras = teste_palestras->first;
                
                printf("\n\n***\tSaida: \t\t(impressao da lista de palestras tratada)");
                
                while(aux_estras)
                {
                    printf("\n\n## ---- ##\n");
                    
                    printf("\nNome da Palestra n.%d: %s", i+1, aux_estras->p->nome_palestra );
                    printf("\nResponsavel: %s\n", aux_estras->p->responsavel);
                    printf("\nTema: %s\n", aux_estras->p->tema);
                    printf("\nLocal: %s\n", aux_estras->p->local);
                    printf("\nDuracao Bruta: %s\n", aux_estras->p->duracao_bruta);
                    printf("\nDuracao tratada: %d\n", aux_estras->p->duracao_tratada);
                    aux_estras = aux_estras->pnext;
                    i++;
                }*/
                
                getchar();
                
                //teste_calendario = Cria_Calendario(teste_palestrantes, teste_palestras);
                aux_cal=teste_calendario;
                
                printf("\n*************************************************\n");
                while(aux_cal)
                {
                    if(aux_cal->marcado == 1)
                    {
                        printf("agenda:\n");
                        aux_agenda=aux_cal->agenda;
                        while(aux_agenda)
                        {
                            printf("\n\nPalestrante: %s\npalestras:",aux_agenda->nome_palestrante);
                            aux_pal = aux_agenda->palestras;
                            while(aux_pal)
                            {
                                printf("palestra: %s ",aux_pal->nome_palestra);
                                printf("horario: \ninicio:%d:%d %d:%d\n",aux_pal->inicio_palestra/60, aux_pal->inicio_palestra%60,aux_pal->fim_palestra/60,aux_pal->fim_palestra%60);
                                aux_pal=aux_pal->prox;
                            }
                            aux_agenda = aux_agenda->prox;
                        }
                    }
                    aux_cal=aux_cal->prox;
                }
                
                 
                printf("\n\n***\t\t");
                
            }

    /* _END_SUITE_ */
    
    /* _SUITE_LISTA_ */
        /*Testes da função x*/
            void Cria_ListaPalestrantes_1(void)
            {
                ListaPalestrantes* header = Cria_ListaPalestrantes();
                CU_ASSERT_PTR_NOT_NULL(header);
                Destroi_ListaPalestrantes(header);
                
            }
            
            void Cria_ListaPalestras_1(void)
            {
                ListaPalestras* header = Cria_ListaPalestras();
                CU_ASSERT_PTR_NOT_NULL(header);
                Destroi_ListaPalestras(header);
            }
            
            void Limpa_ListaPalestras_1(void)
            {
                Palestra* p;
                ListaPalestras* header = Cria_ListaPalestras();
                Insere_Inicio_ListaPalestras(header,p);
                Insere_Inicio_ListaPalestras(header,p);
                Limpa_ListaPalestras(header);
                CU_ASSERT_TRUE(Quant_Elementos_ListaPalestras(header) == 0);
                Destroi_ListaPalestras(header);
            }
            
            void Limpa_ListaPalestrantes_1(void)
            {
                Palestrante* p;
                ListaPalestrantes *header = Cria_ListaPalestrantes();
                Insere_Inicio_ListaPalestrantes(header,p);
                Insere_Inicio_ListaPalestrantes(header,p);
                Limpa_ListaPalestrantes(header);
                CU_ASSERT_TRUE(Quant_Elementos_ListaPalestrantes(header) == 0);
                Destroi_ListaPalestrantes(header);
            }
            
            
            void Info_Corrente_ListaPalestras_1(void)
            {
                Palestra *p;
                p = malloc(sizeof(Palestra));
                ListaPalestras* header = Cria_ListaPalestras();
                Insere_Inicio_ListaPalestras(header,  p);
                Aponta_Inicio_ListaPalestras(header);
                Palestra* paux = Info_Corrente_ListaPalestras(header);
                CU_ASSERT_TRUE(paux == p);
                Destroi_ListaPalestras(header);
            }
            
               void Info_Corrente_ListaPalestrantes_1(void)
            {
                Palestrante *p;
                p=malloc(sizeof(Palestrante));
                ListaPalestrantes* header = Cria_ListaPalestrantes();
                Insere_Inicio_ListaPalestrantes(header,  p);
                Palestrante* paux = Info_Corrente_ListaPalestrantes(header);
                CU_ASSERT_TRUE(paux == p);
                Destroi_ListaPalestrantes(header);
            }
            void Altera_Corrente_ListaPalestrantes_1()
            {
                Palestrante* p;
                Palestrante* p1 = malloc(sizeof(Palestrante));
                p = malloc(sizeof(Palestrante));
                ListaPalestrantes* header = Cria_ListaPalestrantes();
                Insere_Final_ListaPalestrantes(&header,p);
                Aponta_Inicio_ListaPalestrantes(header);
                Altera_Corrente_ListaPalestrantes(header,p1);
                CU_ASSERT_TRUE(Info_Corrente_ListaPalestrantes(header) == p1)
                
            }
            
            void Altera_Corrente_ListaPalestras_1()
            {
                Palestra* p;
                Palestra* p1 = malloc(sizeof(Palestra));
                p = malloc(sizeof(Palestra));
                ListaPalestras* header = Cria_ListaPalestras();
                Insere_Final_ListaPalestras(header,p);
                Aponta_Inicio_ListaPalestras(header);
                Altera_Corrente_ListaPalestras(header,p1);
                CU_ASSERT_TRUE(Info_Corrente_ListaPalestras(header) == p1)
                
            }    
            void Insere_Final_ListaPalestrantes_1()
            {
                Palestrante* p;
                ListaPalestrantes* header = Cria_ListaPalestrantes();
                Insere_Final_ListaPalestrantes(&header, p);
                CU_ASSERT_TRUE(1 == Quant_Elementos_ListaPalestrantes(header));
                Destroi_ListaPalestrantes(header);
            }
            
              void Insere_Final_ListaPalestras_1()
            {
                Palestra* p;
                ListaPalestras* header = Cria_ListaPalestras();
                Insere_Final_ListaPalestras(header, p);
                CU_ASSERT_TRUE(1 == Quant_Elementos_ListaPalestras(header));
                Destroi_ListaPalestras(header);
            }
            
            
    /* _END_SUITE_ */
    
///IMPLEMENTAÇÕES_DAS_SUITES_END

void adicionar_testes(void)
{
    
    CU_pSuite SUITE_CALENDARIO;
    CU_pSuite SUITE_LISTA;
    
        
    /* SUITE_CALENDARIO */
        SUITE_CALENDARIO = CU_add_suite("Testes da suite SUITE_CALENDARIO",NULL,NULL);
            CU_ADD_TEST(SUITE_CALENDARIO, Cria_Grade_1);
            //CU_ADD_TEST(SUITE_CALENDARIO, Cria_Calendario_2);
            CU_ADD_TEST(SUITE_CALENDARIO, Le_palestrantes_1);
            CU_ADD_TEST(SUITE_CALENDARIO, Le_palestrantes_2);
    /* _END_ */
    
    /* SUITE_LISTA */
        SUITE_LISTA = CU_add_suite("Testes dos mods Listas", NULL, NULL);
            CU_ADD_TEST(SUITE_LISTA, Cria_ListaPalestrantes_1);
            CU_ADD_TEST(SUITE_LISTA, Cria_ListaPalestras_1);
            CU_ADD_TEST(SUITE_LISTA, Limpa_ListaPalestras_1);
            CU_ADD_TEST(SUITE_LISTA, Limpa_ListaPalestrantes_1);
            CU_ADD_TEST(SUITE_LISTA, Info_Corrente_ListaPalestras_1);
            CU_ADD_TEST(SUITE_LISTA, Info_Corrente_ListaPalestrantes_1);
            CU_ADD_TEST(SUITE_LISTA, Insere_Final_ListaPalestrantes_1);
            CU_ADD_TEST(SUITE_LISTA, Insere_Final_ListaPalestras_1);
            CU_ADD_TEST(SUITE_LISTA, Altera_Corrente_ListaPalestrantes_1);
            CU_ADD_TEST(SUITE_LISTA, Altera_Corrente_ListaPalestras_1);
    /* _END_ */

}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry())
         return CU_get_error();

        adicionar_testes();

        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        CU_cleanup_registry();

        return CU_get_error();

}




