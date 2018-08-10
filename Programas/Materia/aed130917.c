#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0
#define MAX 50
typedef int bool;
typedef int TIPOCHAVE;
typedef struct{
	TIPOCHAVE chave;
}REGISTRO;
typedef struct{
	int topo;
	REGISTRO A[MAX];
}PILHA;

void inicializar(PILHA* p){
	p->topo = -1;
}

int tamanho(PILHA* p){
	return p->topo+1;
}

int tamanhoEmBytes(){
	return sizeof(PILHA);
}

void exibir(PILHA* p){
	int x;
	printf("Pilha: \" ");
	for(x=p->topo; x >= 0;x--){
		printf("%i ", p->A[x].chave);
	}
	printf("\"\n");                    //  \" imprime o caracter aspas.
}

bool inserir(PILHA* p, REGISTRO reg){
	if(p->topo == MAX-1) return false;
	p->topo++;
	p->A[p->topo] = reg;
	return true;
}

bool excluir(PILHA* p, REGISTRO* reg){
	if(p->topo == -1) return false;
	*reg = p->A[p->topo];
	p->topo--;
	return true;
}

/*REGISTRO* excluir(PILHA* p){              //Memoria que o usuario alocou.
	if(p->topo == -1) return NULL;
	REGISTRO* res=(REGISTRO) malloc(sizeof(REGISTRO));
	*res = p->A[p->topo];
	p->topo--;
	return res;
}
*/
int main(){
	PILHA p1;
	inicializar(&p1);
	exibir(&p1);
	REGISTRO r1;
	excluir(&p1,&r1);
	system("pause");
	/*
	Exemplo de ponteiro
	PONT atual = l->cabeca->prox;
	 "" = (*(l->cabeca)).prox;
	 "" = (*l).cabeca->prox;
	 "" = (*((*l).cabeca)).prox;
	*/
}