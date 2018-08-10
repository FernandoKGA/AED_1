/* LISTA LIGADA -- IMPLEMENTAÇÃO DINÂMICA */
#include <malloc.h>

typedef struct aux{
    REGISTRO reg;
    struct aux* prox;      //Cria ponteiro para o mesmo de ELEMENTO. (palavra ELEMENTO ainda não apareceu por isso se usa essa struct).
}ELEMENTO, *PONT; //*PONT - Ponteiro para ELEMENTO. (typedef ELEMENTO* PONT) - Tipo PONT que é ponteiro de elemento (tipo de dado, não variável como acima).;

typedef struct{
    PONT inicio;
}LISTA;

void inicializar(LISTA* l){
    l->inicio = NULL;
}

int tamanho(LISTA l){ //Como você está passando uma LISTA que tem somente um campo PONT que é ponteiro, não faz diferença passar cópia. O que muda é o acesso.
    PONT atual = l.inicio;  //Atual recebe o ponteiro do inicio da lista.    /*Caso use ponteiro, parâm. (LISTA* l), acesso: PONT atual = l->inicio  ; ou seja, acessa inicio. */
    int tam = 0;   //Inicializa tamanho.
    while(atual){
        tam++; //Aumenta 1 em tamanho.
        atual = atual-> prox;   //Vai para o próximo endereço de prox.
    }
    return tam;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE  ch, PONT* ant){ //Se fosse só busca, não tem problema mandar cópia.  PONT*  = ELEMENTO** é um ponteiro para ponteiro de elemento.
    *ant = NULL;
    PONT atual = l->inicio;
    while(atual != NULL && atual->reg.chave<ch){    //Acessa o campo chave de REGISTRO, ou seja, do ELEMENTO.
        *ant = atual;  //Vá na memória da variável do tipo PONT e coloque o atual lá(seu ponteiro).
        atual = atual->prox;
    }
    if(atual != NULL && atual->reg.chave == ch) return atual;
    return NULL;
}

bool excluir(LISTA* l, TIPOCHAVE ch){
    PONT ant, atual;
    atual = buscaSeqExc(l, ch, &ant);
    if(atual == NULL) return false;
    if(ant == NULL) l->inicio = atual->prox;
    else ant->prox = atual->prox;
    /*else ant->prox = ant->prox->prox; */
    free(atual);
    return true;
}

bool inserirOrd(LISTA* l, REGISTRO reg){
    PONT ant, atual;
    atual = buscaSeqExc(l, reg.chave, &ant);
    if(atual) return false;
    atual = (PONT) malloc(sizeof(ELEMENTO));
    atual->reg = reg;
    if(ant == NULL){
        atual->prox = l->inicio;
        l->inicio = atual;
    }
    else{
        atual->prox = ant->prox;
        ant->prox = atual;
    }
    return true;
}

void reinicializar(LISTA* l){
    PONT apagar, atual;
    atual = l->inicio;
    while(atual){
        apagar = atual;
        atual = atual->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

int main(){
    LISTA l1;
    inicializar(&l1);
    int x = tamanho(l1);   //tamanho(&l1) caso seja ponteiro.
}
