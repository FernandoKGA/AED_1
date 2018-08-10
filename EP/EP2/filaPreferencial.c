#include "filaPreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  PONT cab =  (PONT) malloc(sizeof(REGISTRO));
  cab->id = -1;
  cab->idade = -1;
  cab->antFila = cab;
  cab->proxFila = cab;
  cab->antIdade = cab;
  cab->proxIdade = cab;
  res->cabeca = cab;
  return res;
}

bool exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("Log fila [elementos: %i]\n", numElementos);
  PONT atual = f->cabeca->proxFila;
  while (atual != f->cabeca){
    printf("%p[%i;%i;%p]%p ", atual->antFila, atual->id, atual->idade, atual, atual->proxFila);
    atual = atual->proxFila;
  }
  printf("\nLog preferencial [elementos: %i]\n", numElementos);
  atual = f->cabeca->proxIdade;
  while (atual != f->cabeca){
    printf("%p[%i;%i;%p]%p ", atual->antIdade, atual->id, atual->idade, atual, atual->proxIdade);
    atual = atual->proxIdade;
  }
  printf("\n\n");
}
//COMPLETO
bool consultarIdade(PFILA f, int id, int* resposta){
	PONT atual;               //Criacao de ponteiro chamado elemento.
	atual = f->cabeca->proxFila;     //Recebe a cabeca.
	if(id>=0){                            //Evitar que o id que ele deseja seja o cabeca e corrompa a fila.
		while(atual != f->cabeca){          //Enquanto for diferente de cabeca, roda o laco.
			if(atual->id == id){         //Caso acho o id igual ao desejavel.
				*resposta = atual->idade;         //Guarda no endereco de resposta, a idade do elemento.
				return true;                //Retorna true pois achou.
			}
			atual = atual->proxFila;     //Pega o proximo elemento se nao achou.
		}
	}
	return false;
}
//COMPLETO
int tamanho(PFILA f){
	int tam = 0;
	PONT atual;  //Cria um ponteiro de um elemento.
	atual = f->cabeca->proxFila;        //Pega o proximo de cabeca.
	while(atual != f->cabeca){         //Verifica se o elemento eh diferente de cabeca. Se for entra no laco.
		tam++;
		atual = atual->proxFila;   //Pega o proximo do elemento.
	}
	return tam;
}
//AUXILIAR COMPLETO
PONT preencheElemento(int id, int idade){
	PONT reg = (PONT) malloc(sizeof(REGISTRO));
	PONT atual;
	atual = reg;
	atual->id = id;
	atual->idade = idade;
	atual->proxFila = atual;
	atual->antFila = atual;
	atual->antIdade = atual;
	atual->proxIdade = atual;
}
//COMPLETO
bool inserirElemento(PFILA f, int id, int idade){
	if((f->cabeca->proxFila == f->cabeca) && (id > 0) && (idade > 0)){      //"cabeca" so existe dentro de FILA.  Insere o primeiro elemento na fila caso nao exista.
        PONT atual = preencheElemento(id,idade);
        atual->proxFila = f->cabeca;          //Apontam para a cabeca.
        atual->antFila = f->cabeca;
        atual->proxIdade = f->cabeca;
        atual->antIdade = f->cabeca;
        f->cabeca->proxFila = atual;          //Apontam para o primeiro da fila.
        f->cabeca->antFila = atual;
        f->cabeca->proxIdade = atual;
        f->cabeca->antIdade = atual;
        return true;
	}
	int resposta;    //Aloca uma memoria para receber a resposta.
	if(consultarIdade(f, id, &resposta) == true){   //Existe elemento com mesmo id. Entao retorna false para impedir ser inserido.
		return false;
	}
	else{
        if((f->cabeca->proxFila != f->cabeca) && (id > 0) && (idade > 0)){
            PONT atual = preencheElemento(id,idade);
            PONT verifIdade;
            atual->proxFila = f->cabeca;                //Indica para a cabeca o final da fila.
            atual->antFila = f->cabeca->antFila;        //Pega o que era anterior a cabeca.
            atual->antFila->proxFila = atual;           //Modifica o proxFila do anterior para apontar para o novo fim.
            f->cabeca->antFila = atual;                 //Aponta o anterior de cabeca para atual como novo fim.
            verifIdade = f->cabeca->proxIdade;          //Pega o preferencial da cabeca (maior elemento na ordem).
            while(verifIdade != f->cabeca){
                if((atual->idade) > (verifIdade->idade)){
                    atual->proxIdade = verifIdade;
                    atual->antIdade = verifIdade->antIdade;
                    verifIdade->antIdade = atual;
                    atual->antIdade->proxIdade = atual;
                    break;
                }
                if((atual->idade) < (f->cabeca->antIdade->idade)){
                    atual->proxIdade = f->cabeca;      //Por ser o menor, aponta para a cabeca.
                    atual->antIdade = f->cabeca->antIdade;   //Pega o anterior da cabeca que seria o antigo menor.
                    f->cabeca->antIdade->proxIdade = atual; //Por ser menor que o ultimo, ele acessa o anterior idade da cabeca e substitui o proximo de cabeca para o elemento atual.
                    f->cabeca->antIdade = atual; //O antIdade de cabeca passa ah apontar para o menor de todos a partir de entao.
                    break;
                }
                if((atual->idade) == (verifIdade->idade)){
                    while(verifIdade->proxIdade->idade == atual->idade){
                        verifIdade = verifIdade->proxIdade;
                    }
                    atual->proxIdade = verifIdade->proxIdade;
                    atual->antIdade = verifIdade;
                    verifIdade->proxIdade->antIdade = atual;
                    verifIdade->proxIdade = atual;
                    break;
                }
                verifIdade = verifIdade->proxIdade;
            }
            return true;
        }
	}
	return false;
}
//AUXILIAR PARA MOVER PONTEIROS PARA REMOCAO
PONT movePonteiros(PONT elemento){
    elemento->proxFila->antFila = elemento->antFila;
    elemento->antFila->proxFila = elemento->proxFila;
    elemento->proxIdade->antIdade = elemento->antIdade;
    elemento->antIdade->proxIdade = elemento->proxIdade;
}

//COMPLETO
PONT removerElementoIdade(PFILA f){
    PONT elemento;
    elemento = f->cabeca->proxIdade;
    if(elemento != f->cabeca){
        movePonteiros(elemento);
        return elemento;
    }
	return NULL;
}


//COMPLETO
PONT removerElementoFila(PFILA f){
    PONT elemento;
    elemento = f->cabeca->proxFila;
    if(elemento != f->cabeca){
        movePonteiros(elemento);
        return elemento;
    }
	return NULL;
}
//COMPLETO
bool abandonarFila(PFILA f, int id){
    PONT elemento;
    elemento = f->cabeca->proxFila;
    if(elemento != f->cabeca){
        while(elemento != f->cabeca){
            if(id == elemento->id){
                movePonteiros(elemento);
                free(elemento);
                return true;
            }
            elemento = elemento->proxFila;
        }
    }
	return false;
}
