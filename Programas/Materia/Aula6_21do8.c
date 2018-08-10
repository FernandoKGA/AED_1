#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1    //Tipos booleanos não existem(true,false) em C.
#define false 0
typedef int bool;
typedef int TIPOCHAVE;    //Inteiro com nome de chave para o código ficar mais legível.
typedef struct{
    TIPOCHAVE chave;
    /*Outras coisas*/
}REGISTRO
typedef struct{
    REGISTRO A[MAX+1];   //Arranjo de REGISTROS, não de ponteiros para estruturas.
    int nroElem;     //Campo para colocar quantos elementos existem.
}LISTA;
void inicializar(LISTA* l){   //Pergunta de prova: Essa função pode receber uma cópia de LISTA?(Quanto de memória estaria sendo copiada?).
    l->nroElem = 0;           //Cont.: Vai funcionar o que o código exige? Não, ele não modifica a original.
}                             //O ponteiro acessa o arranjo lista através do ponteiro e coloca em nroElem o 0.
bool inserir(LISTA* l,REGISTRO reg, int i){   //Passa o REGISTRO e sua posição para inserção na lista.
    int x;
    if((l->nroElem >= MAX)||(i<0)||(i>l->nroElem)) return false;
    for(x=l->nroElem;x>i;i--) l->A[x] = l->A[x-1];  //Move os elementos para abrir espaço para o novo registro.
    l->A[i] = reg; //Coloca o registro(toda a estrutura do registro) na posição(válida) dada pelo usuário.
    l->nroElem++; //Aumenta o número de elementos pela lógica que se adicionou mais um elemento.
    return true;
}
int buscaSeq(LISTA* l, TIPOCHAVE ch){
    int x = 0;  //Interador.
    while(x < l->nroElem){
        if(l->A[x].chave == ch) return x;   //(A[x].chave é o elemento da Lista, não seu endereço)(Caso fosse arranjo de ponteiros seria com ->)
        x++;                                //O while vai caçar dentro do arranjo um elemento chave que seja igual ao passado pelo usuário.
    }
    return ERRO;
}
int buscaSent(LISTA* l, TIPOCHAVE ch){
    int x=0;
    l->A[l->nroElem].chave = ch; //Coloca a sentinela no final do arranjo (MAX+1) para que caso não exista ele pare o laço.
    while(l->A[x].chave != ch)x++;   //(Dentro desse laço só tem 1 teste, não 2 como na outra, reduz na metade o tempo de busca.
    if(x == l->nroElem) return ERRO;
    return x;
}
int tamanhoEmByte(){
    sizeof(LISTA* l) //Ver no site da disciplina.}
bool excluir(LISTA* l, TIPOCHAVE ch){
    int pos, x;
    pos = buscaSeq(l, ch);
    if(pos == ERRO) return false; //Caso ele não ache o elemento na lista ele já dá erro.
    for(x=pos;x<l->nroElem-1;x++) l->A[x] = l->A[x+1];  //Ele volta um campo na lista excluindo o elemento e copiando respectivamente os elementos para não sobrar espaços, assim como na inserção que avança.
    l->nroElem--;  //Diminui o número global de elementos da lista.
    return true;
}
int main(){
    LISTA lista;
    inicializar(&lista);
    r.chave = 8;
    inserir(&lista, r, 1);   //Recebe uma chave(aqui como inteiro) no parâmentro, caso fosse uma estrutura grande, colocar a chave.
    excluir(&lista, r);
}
