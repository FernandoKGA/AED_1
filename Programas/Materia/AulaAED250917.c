#include <stdio.h>
#define ERRO -1
#define MAX 50
#define true 1
#define false 0
typedef int TIPOCHAVE

typedef struct{
	TIPOCHAVE chave;
}REGISTRO;

typedef struct{
	REGISTRO A[MAX];
	int inicio;
	int nroElem;
}FILA;

void inicializar(FILA* f){
	f->nroElem = 0;
	f->inicio = 0;

}

int tamanho(FILA* f){
	return f->nroElem;
}

int tamanhoEmBytes(){
	return sizeof(FILA);
}
//Função de exibir fila.
int buscaSeq(FILA* f, TIPOCHAVE ch){
	int atual = f->inicio;
	int x;
	for(x=0;x < f->nroElem, x++){
		if(f->A[atual].chave == ch) return atual;
		atual = (atual+1)%MAX;	
	}
	return ERRO;
}
//fim = (inicio+nroElem-1) % MAX
//novo = (inicio+nroElem-1) % MAX

bool excluir(FILA* f, REGISTRO* reg){
	if(f->nroELem == 0) return false;
	*reg = f->A[f->inicio];
	f->nroElem--;
	f->inicio = (inicio+1) % MAX;
	return true;
}

bool inserir(FILA* f, REGISTRO reg){
	if(f->nroELem == MAX) return false;
	f->A[(f->inicio + f->nroElem)%MAX] = reg;
	f->nroElem++;
	return true;
}

void reinicializar(FILA* f){
	inicializar(f);    //Ele espera receber um endereço de fila, e o reinicializar recebe um endereço, então só colocar o próprio f.
}

//Matheus vai me dar R$100k se ganhar na mega sena(depende de quanto ganhar)
int main(){
REGISTRO rx;
excluir(&f1,&rx);
return 0;
}

//Usar nroElementos nos salva de casos que o fim e inicio fariam com que ou a fila estaria cheia, ou vazia, e o código para isso fica maior para não gerar ambiguidade, o que não acontece com o campo nroElementos.


