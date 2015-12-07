enquanto nao acabar as palestras
{
    enquanto nao acabar os palestrantes e nao tiver alocado
    {
        analisa a lista de palestrantes até encontrar qual é responsavel pela palestra analisada
        se achou o Palestrante
        {
            enquanto nao acabar a lista de disponibilidade do palestrante encontrado e nao tiver alocado
            {
                analisa a duração da palestra com a duração da disponibiliade do palestrante encontrado
                se a duração da disponibilidade do palestrante é >= a duração da palestra
                {
                   enquanto nao acabar os locais e nao tiver alocado
                    {
                        enquanto não acabar a lista de disponibilidade do local analisado
                        {
                            analisa a duração da palestra com a duração da disponibilidade do local analisado

                            se a duração da disponibilidade do local é >= a duração da Palestra
                            {
                                se o campo dia da disponibilidade do local analisada é = ao do palestrante analisado
                                {
                                    inicio = maximo entre a hora de inicio da disponibilidade do palestrante e hora de inicio do local
                                    final = minimo entre a hora de fim da disponibilidade do palestrante e hora de inicio do local

                                    duração_alocacao = final - inicio

                                    se duracao_alocacao >= duracao da palestra
                                    {
                                        pode alocar, ou seja, cria novo elemento para ser inserido no calendario, sei lah!!!
                                        break
                                    }
                                    senao
                                    {
                                        vai para a proxima disponibilidade do local
                                    }

                                }
                                senao
                                {
                                    vai para a proxima disponibilidade do local
                                }
                            }
                            se nao
                            {
                                vai para a proxima disponibilidade do local
                            }
                        }
                        vai para o proximo local
                    }
                }

                vai para a proxima disponibilidade do palestrante
            }
        }
        vai para o proximo palestrante
    }
}
