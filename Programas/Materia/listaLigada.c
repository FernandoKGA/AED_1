/******************************************************************************
//     listaLigadaEstatica.c
// Este programa gerencia listas lineares ligadas (implementacao estatica).
// As listas gerenciadas podem ter MAX elementos (posicoes de 0 a MAX-1 no
//   arranjo A). Não usaremos sentinela nesta estrutura.
******************************************************************************/
#include <stdio.h>      //Não utiliza Busca Binária neste tipo de Lista.
#define MAX 50          //Foi utilizado como máximo na aula, 6 espaços.
#define INVALIDO -1
#define true 1
#define false 0
typedef int bool;

typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct{
  REGISTRO reg;
  int prox;
} ELEMENTO;

typedef struct {
  ELEMENTO A[MAX];
  int inicio;
  int dispo;
} LISTA;

/* Inicialização da lista sequencial (a lista jah esta criada e eh apontada
pelo endereco em l) */
void inicializarLista(LISTA* l){
  int i;
  l->inicio=INVALIDO;
  l->dispo=0;
  for (i=0; i<MAX-1; i++)
    l->A[i].prox = i + 1;
  l->A[MAX-1].prox = INVALIDO;
} /* inicializarLista */

/* Exibição da lista sequencial */
void exibirLista(LISTA* l){
  int i = l->inicio;
  printf("Lista: \" ");
  while (i != INVALIDO){
    printf("%d ", l->A[i].reg.chave); // soh lembrando TIPOCHAVE = int
    i = l->A[i].prox;
  }
  printf("\"\n");
} /* exibirLista */

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamanho(LISTA* l) {
  int i = l->inicio;
  int tam = 0;
  while (i != INVALIDO){
    tam++;
    i = l->A[i].prox;
  }
  return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto nao depende do numero
   de elementos que estao sendo usados, pois a alocacao de memoria eh estatica.
   A priori, nao precisariamos do ponteiro para a lista, vamos utiliza-lo apenas
   porque teremos as mesmas funcoes para listas ligadas implementacao nao estatica.
*/
int tamanhoEmBytes(LISTA* l) {
  return sizeof(LISTA);
} /* tamanhoEmBytes */

/* Busca sequencial (lista ordenada ou nao) */
int buscaSeq(LISTA* l, TIPOCHAVE ch){
  int i = l->inicio;
  while (i != INVALIDO){
    if (l->A[i].reg.chave == ch) return i;
    i = l->A[i].prox;
  }
  return INVALIDO;
} /* buscaSeq */

/* Busca sequencial - funcao de exclusao (retorna no endereço *ant o indice do
   elemento anterior ao elemento que está sendo buscado [ant recebe o elemento
   anterior independente do elemento buscado ser ou não encontrado]) */
int buscaSeqExc(TIPOCHAVE ch, LISTA* l, int *ant){
  *ant = INVALIDO;                    //i é o indíce atual.
  int i = l->inicio;
  while ((i != INVALIDO) && (l->A[i].reg.chave<ch)){
    *ant = i;
    i = l->A[i].prox;
  }
  if ((i != INVALIDO) && (l->A[i].reg.chave == ch)) return i;
  return INVALIDO;
} /* buscaSeqExc */

/* Obter nó disponível e marcá-lo como não disponível - esta operação será usada
  junto com inserções, por exemplo */
int obterNo(LISTA* l){
  int resultado = l->dispo;
  if (l->dispo != INVALIDO) l->dispo = l->A[l->dispo].prox;
  return resultado;
} /* obterNo */

/* Devolver nó da posição j para a lista de nós disponíveis - coloca-se o nó j
   como primeiro na lista de disponíveis */
void devolverNo(LISTA* l, int j){
     l->A[j].prox = l->dispo;
     l->dispo = j;
} /* devolverNo */

bool excluirElemLista(LISTA* l, TIPOCHAVE ch){
  int ant = INVALIDO;
  int i = l->inicio;
  while ((i != INVALIDO) && (l->A[i].reg.chave<ch)){
    ant = i;
    i = l->A[i].prox;
  }
  if (i==INVALIDO || l->A[i].reg.chave!=ch) return false;
  if (ant == INVALIDO) l->inicio = l->A[i].prox;
  else l->A[ant].prox = l->A[i].prox;
  devolverNo(l,i);
  return true;
} /* excluirElemListaEnc */


/* Exclusão do elemento de chave indicada */
bool excluirElemLista2(LISTA* l, TIPOCHAVE ch){
  int ant, i;
  i = buscaSeqExc(ch, l, &ant);
  if (i == INVALIDO) return false;
  if (ant == INVALIDO) l->inicio = l->A[i].prox; //Se for o início.
  else l->A[ant].prox = l->A[i].prox;  //Caso exista aponta para o próximo do excluído.
  l->A[atual].prox = l->dispo;
  l->dispo = atual;
  devolverNo(l,i);
  return true;
} /* excluirElemListaEnc */



/* Destruição da lista sequencial */
void reinicializarLista(LISTA* l) {
  inicializarLista(l);
} /* destruirLista */


/* Inserção em lista ordenada sem duplicação */
bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  if (l->dispo == INVALIDO) return false; // se lista cheia, não é possível inserir
  int ant = INVALIDO;
  int i = l->inicio;
  while ((i != INVALIDO) && (l->A[i].reg.chave<reg.chave)){
    ant = i;
    i = l->A[i].prox;
  }
  if (i!=INVALIDO && l->A[i].reg.chave==reg.chave) return false;
  i = obterNo(l);
  l->A[i].reg = reg;
  if (ant == INVALIDO) { // o novo elemento será o 1o da lista (a lista podia estar vazia ou não)
    l->A[i].prox = l->inicio;
    l->inicio = i;
  } else {  // inserção após um elemento já existente
    l->A[i].prox = l->A[ant].prox;
    l->A[ant].prox = i;
  }
  return true;
} /* inserirElemListaOrd */

bool inserirOrd(LISTA* l, REGISTRO reg){
    if(l->dispo==INVALIDO) return false;
    int ant;
    int i = buscaSeqExc(l, reg.chave, &ant);
    if(i != INVALIDO) return false;
    i = l->dispo;
    l->A[i].reg = reg;
    l->dispo = l-> A[i].prox;
    if(ant == INVALIDO){l->inicio = A[i].chave
        l->A[i].prox = l->inicio;
        l->inicio = i;
    }
    else{
        l->A[i].prox = l->A[ant].prox;
        l->A[ant].prox = i;
    }
    return true;
}
