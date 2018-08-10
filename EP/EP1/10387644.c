#include "filaPreferencial.h"

/*		NOME: FERNANDO KARCHILOFF GOUVEIA DE AMORIM    */
/*		NUM. USP: 10387644			ACH2023 - TURMA04		   */
/*		DATA:		11/09/2017		PROF. LUCIANO DIGIAMPIETRI*/

PFILA criarFila(){    //Cria a fila.
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));    //Aloca tamanho para lista preferencial.
  res->inicioFila = NULL;
  res->fimFila = NULL;
  res->preferencial = NULL;
  return res;
}

bool exibirLog(PFILA f){   //Roda um log simples.
  int numElementos = tamanho(f);
  printf("Log fila [elementos: %i]\n", numElementos);
  PONT atual = f->inicioFila;
  while (atual){
    printf("%p[%i;%i;%p]%p ", atual->antFila, atual->id, atual->idade, atual, atual->proxFila);
    atual = atual->proxFila;
  }
  printf("\nLog preferencial [elementos: %i]\n", numElementos);
  atual = f->preferencial;
  while (atual){
    printf("%p[%i;%i;%p]%p ", atual->antIdade, atual->id, atual->idade, atual, atual->proxIdade);
    atual = atual->proxIdade;
  }
  printf("\n\n");
}


bool consultarIdade(PFILA f, int id, int* resposta){         //Pega a fila em questao, o id e o ponteiro para a variavel.
    PONT atual = f->inicioFila;                           //Pega o inicio da fila.
    while(atual){                                //Enquanto houver inicio da fila (diferente de NULL), ele roda o laco.
        if(id == atual->id){                      //Caso ache o id igual ah um que exista na lista.
            *resposta = atual->idade;             //Guarda a idade deste elemento da lista na variavel.
            return true;                
        }
        atual = atual->proxFila;            //Se nao achou, passa para o proximo elemento.
    }
    return false;                        //Se nao existe, retorna falso.
}

int tamanho(PFILA f){ 
    PONT atual = f->inicioFila;  //Aloca uma variavel que recebe um ponteiro do primeiro elemento da fila.(Caso exista.)
    int tam = 0;  //Inicializa tamanho como 0;
    while(atual){   //Caso nao seja NULL, roda o while.
        tam++;  //Aumenta 1 em tamanho se entrou aqui.
        atual = atual->proxFila;  //Vai no ponteiro que eh um REGISTRO, e pega do campo proxFila o proximo ponteiro e o armazena.
    }
    return tam;         //Retorna o tamanho calculado da lista.
}

PONT preencheReg(int id, int idade){   //Preenche um registro a ser criado.
    PONT reg = (PONT) malloc(sizeof(REGISTRO));        //Aloca um espaco na memoria para esse registro.
    reg->id = id;   //Coloca o id respectivo.
    reg->idade = idade;  //Coloca a idade respectiva.
    reg->antFila = NULL;          //Seta os campos do registro como nulo.
    reg->antIdade = NULL;
    reg->proxFila = NULL;
    reg->proxIdade = NULL;
    return reg;          //Retorna o proprio registro.
}

bool inserirElemento(PFILA f, int id, int idade){
    if((f->inicioFila == NULL) && (id>=0) && (idade>=0)){  //Caso nao haja registros na lista.
        PONT reg = preencheReg(id, idade);  //Recebe o endereco do registro criado.
        f->inicioFila = reg;  //Recebe o elemento nos campos da fila.
        f->preferencial = reg;
        f->fimFila = reg;
        return true;
    }
    if((f->inicioFila != NULL) && (id>=0) && (idade>=0)){   //Se ja existe um ou mais elementos.
        int resposta;    //Aloca um espaco para resposta.
        if(consultarIdade(f,id,&resposta) == true){  //Consulta se ja existe "id" igual.
            return false;   //Ja tem id igual. Entao retorna "false" para nao ser inserido.
        }
        else{  //Se ele chegou aqui nao tem "id" igual e assim pode inserir.
            PONT reg = preencheReg(id, idade);  //Cria o registro a ser colocado.
            PONT atual, verfIdade;
            atual = f->fimFila;
            atual->proxFila = reg;
            reg->antFila = atual;
            f->fimFila = reg;  //Coloca no fim da fila.
            atual = f->fimFila;  //Pega o novo fim da fila.
            verfIdade = f->preferencial;          //Guarda o preferencial para verificacao.
            if((atual->idade)>(f->preferencial->idade)){         //Caso a idade do atual seja maior que a idade do preferencial.
                atual->proxIdade = f->preferencial;
                f->preferencial->antIdade = atual;
                f->preferencial = atual;
                return true;
            }
            else{
                if((atual->idade)<(f->preferencial->idade)){        //Caso a idade do atual seja menor do que a do preferencial.
                    while(verfIdade->proxIdade != NULL){   //Verifica a fila para caso o elemento tenha de ser inserido entre outros.  (verfIdade->proxIdade != null (diferente), para impedir caso nao haja outro elemento ah frente ele sair).
                        if((verfIdade->proxIdade->idade)<(atual->idade)){   //Quando acha um elemento menor que o atual a ser colocado.
                            verfIdade->proxIdade->antIdade = atual;
                            atual->proxIdade = verfIdade->proxIdade;
                            atual->antIdade = verfIdade;
                            verfIdade->proxIdade = atual;
                            return true;
                        }
                        if((verfIdade->proxIdade->idade)==(atual->idade)){  //Quando idades sao iguais e ids diferentes.
                            if(verfIdade->proxIdade->proxIdade != NULL){         //Quando pode ser que exista mais que 1 igual.
                                if(verfIdade->proxIdade->proxIdade->idade == atual->idade){       //Verifica se existem 2 iguais na fila(para adicionar o terceiro).
                                    while(verfIdade->proxIdade->proxIdade->idade == atual->idade){   //Vai ate quantos iguais houverem.
                                        verfIdade = verfIdade->proxIdade;
                                    }
                                }
                                atual->proxIdade = verfIdade->proxIdade->proxIdade;
                                if(atual->proxIdade != NULL){    //Evitar colocar no registro, memoria nao alocada, pois acessar VOID(NULL) pode gerar erro.
                                   atual->proxIdade->antIdade = atual;
                                }
                                verfIdade->proxIdade->proxIdade = atual;        //Pega o proxIdade do que tem idade igual e coloca o atual la.
                                atual->antIdade = verfIdade->proxIdade;         //Coloca o anterior na antIdade do atual.
                                return true;
                            }
                            else{                //Quando soh tem um(1) igual.
                                verfIdade->proxIdade->proxIdade = atual;
                                atual->antIdade = verfIdade->proxIdade;
                                return true;
                            }
                        }
                        verfIdade = verfIdade->proxIdade;      //Anda para frente na fila preferencial.
                    }
                    if((verfIdade->idade)>(atual->idade)){  //Fora do while para o ultimo elemento da fila.
                        verfIdade->proxIdade = atual;
                        atual->antIdade = verfIdade;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void zeraCamposElemento(PONT elemento){   //Pega um elemento e zera seus campos de fila normal.
    elemento->antFila = NULL;
    elemento->proxFila = NULL;
}

PONT removerElementoIdade(PFILA f){
    PONT maiorIdade;
    maiorIdade = f->preferencial;   //Coloca em um ponteiro o endereco do registro preferencial.
    if(f->inicioFila != NULL){
        if((maiorIdade->antFila == NULL) && (maiorIdade->proxFila == NULL)){       //Se o elemento eh unico na fila, o elimina da fila.
            maiorIdade->proxIdade = NULL;
            f->fimFila = NULL;
            f->inicioFila = NULL;
            f->preferencial = NULL;
            zeraCamposElemento(maiorIdade);
            return maiorIdade;
        }
        if((maiorIdade->antFila != NULL) && (maiorIdade->proxFila != NULL)){  //Caso o elemento esteja entre outros na fila.
            maiorIdade->antFila->proxFila = maiorIdade->proxFila;
            maiorIdade->proxFila->antFila = maiorIdade->antFila;
            zeraCamposElemento(maiorIdade);
        }
        if((maiorIdade->antFila != NULL) && (maiorIdade->proxFila == NULL)){  //ProxFila nulo e antFila nao nulo.   (Caso seja o ultimo da fila).
            maiorIdade->antFila->proxFila = NULL;
            zeraCamposElemento(maiorIdade);
        }
        if((maiorIdade->antFila == NULL) && (maiorIdade->proxFila != NULL)){  //AntFila nulo e proxFila nao nulo.   (Caso seja o primeiro na fila).
            if(f->inicioFila == maiorIdade){
                f->inicioFila = maiorIdade->proxFila;
                maiorIdade->proxFila->antFila = NULL;
                zeraCamposElemento(maiorIdade);
            }
        }
        maiorIdade->proxIdade->antIdade = NULL;   //Acessa o campo proxIdade do registro preferencial e acessa o endereco de la e vai ate o campo antIdade e seta NULL.
        f->preferencial = maiorIdade->proxIdade;  //O novo preferencial vai receber o endereco do proxIdade do antigo preferencial.
        maiorIdade->proxIdade = NULL;   //Exclui-se o proxIdade do antigo preferencial.
        return maiorIdade;   //Retorna seu endereco.
    }
    return NULL;
}



PONT removerElementoFila(PFILA f){
    PONT primeiroFila;
    primeiroFila = f->inicioFila;  //Pega o inicio da fila a ser eliminado em questao.
    if(primeiroFila != NULL){      //Condicao para que exista um elemento, se nao ele retorna fila vazia.
        if((primeiroFila->antIdade)&&(primeiroFila->proxIdade)!= NULL){    //Caso o elemento esteja entre outros elementos da fila preferencial.
            primeiroFila->antIdade->proxIdade = primeiroFila->proxIdade;
            primeiroFila->proxIdade->antIdade = primeiroFila->antIdade;
        }
        if((primeiroFila->antIdade != NULL) && (primeiroFila->proxIdade == NULL)){    //Caso o elemento seja o ultima da fila preferencial.
            primeiroFila->antIdade->proxIdade = primeiroFila->proxIdade;
        }
        if((primeiroFila->antIdade == NULL) && (primeiroFila->proxIdade != NULL)){   //Caso seja o elemento preferencial.
            if(primeiroFila == f->preferencial){        //Verifica novamente se eh o preferencial.
                f->preferencial = primeiroFila->proxIdade;
            }
            primeiroFila->proxIdade->antIdade = NULL;
            primeiroFila->proxIdade = NULL;
        }
        if(f->inicioFila->proxFila != NULL){   //Se tamanho nao eh 1.
            f->inicioFila = primeiroFila->proxFila;
            primeiroFila->proxFila->antFila = NULL;
            zeraCamposElemento(primeiroFila);
        }
        else{      //Se eh o unico na fila.
            zeraCamposElemento(primeiroFila);   //Zera o elemento e todos os seus campos.
            primeiroFila->proxIdade = NULL;
            primeiroFila->antIdade = NULL;
            f->preferencial = NULL;    //Zera a lista.
            f->fimFila = NULL;
            f->inicioFila = NULL;
        }
        return primeiroFila;
    }
    return NULL;
}