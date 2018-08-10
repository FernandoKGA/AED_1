#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1    //Tipos booleanos n�o existem(true,false) em C.
#define false 0
typedef int bool;
typedef int TIPOCHAVE;    //Inteiro com nome de chave para o c�digo ficar mais leg�vel.
typedef struct{
    TIPOCHAVE chave;
    /*Outras coisas*/
}REGISTRO
typedef struct{
    REGISTRO A[MAX+1];   //Arranjo de REGISTROS, n�o de ponteiros para estruturas.
    int nroElem;     //Campo para colocar quantos elementos existem.
}LISTA;
void inicializar(LISTA* l){   //Pergunta de prova: Essa fun��o pode receber uma c�pia de LISTA?(Quanto de mem�ria estaria sendo copiada?).
    l->nroElem = 0;           //Cont.: Vai funcionar o que o c�digo exige? N�o, ele n�o modifica a original.
}                             //O ponteiro acessa o arranjo lista atrav�s do ponteiro e coloca em nroElem o 0.
bool inserir(LISTA* l,REGISTRO reg, int i){   //Passa o REGISTRO e sua posi��o para inser��o na lista.
    int x;
    if((l->nroElem >= MAX)||(i<0)||(i>l->nroElem)) return false;
    for(x=l->nroElem;x>i;i--) l->A[x] = l->A[x-1];  //Move os elementos para abrir espa�o para o novo registro.
    l->A[i] = reg; //Coloca o registro(toda a estrutura do registro) na posi��o(v�lida) dada pelo usu�rio.
    l->nroElem++; //Aumenta o n�mero de elementos pela l�gica que se adicionou mais um elemento.
    return true;
}
int buscaSeq(LISTA* l, TIPOCHAVE ch){
    int x = 0;  //Interador.
    while(x < l->nroElem){
        if(l->A[x].chave == ch) return x;   //(A[x].chave � o elemento da Lista, n�o seu endere�o)(Caso fosse arranjo de ponteiros seria com ->)
        x++;                                //O while vai ca�ar dentro do arranjo um elemento chave que seja igual ao passado pelo usu�rio.
    }
    return ERRO;
}
int buscaSent(LISTA* l, TIPOCHAVE ch){
    int x=0;
    l->A[l->nroElem].chave = ch; //Coloca a sentinela no final do arranjo (MAX+1) para que caso n�o exista ele pare o la�o.
    while(l->A[x].chave != ch)x++;   //(Dentro desse la�o s� tem 1 teste, n�o 2 como na outra, reduz na metade o tempo de busca.
    if(x == l->nroElem) return ERRO;
    return x;
}
int tamanhoEmByte(){
    sizeof(LISTA* l) //Ver no site da disciplina.}
bool excluir(LISTA* l, TIPOCHAVE ch){
    int pos, x;
    pos = buscaSeq(l, ch);
    if(pos == ERRO) return false; //Caso ele n�o ache o elemento na lista ele j� d� erro.
    for(x=pos;x<l->nroElem-1;x++) l->A[x] = l->A[x+1];  //Ele volta um campo na lista excluindo o elemento e copiando respectivamente os elementos para n�o sobrar espa�os, assim como na inser��o que avan�a.
    l->nroElem--;  //Diminui o n�mero global de elementos da lista.
    return true;
}
int main(){
    LISTA lista;
    inicializar(&lista);
    r.chave = 8;
    inserir(&lista, r, 1);   //Recebe uma chave(aqui como inteiro) no par�mentro, caso fosse uma estrutura grande, colocar a chave.
    excluir(&lista, r);
}
