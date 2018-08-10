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

typedef struct aux*{
	REGISTRO reg;
	struct aux* prox;
}ELEMENTO, * PONT;

typedef struct{
	PONT topo;
}PILHA;

void inicializar(PILHA* p){   //Ponteiro RAW, nao foi definido na estrutura dela um Ponteiro que aponte para ela.
	p->topo = NULL;
}

int tamanho(PILHA p){   //Como a estrutura tem um endereco que leva diretamente a PILHA, nao tem problema passar uma copia.
	PONT atual = p.topo;   //Por ser copia usa ponto.
	int tam = 0;
	while(atual){
		tam++;
		atual = atual->prox;
	}
	return tam;
}

int tamanhoEmBytes(PILHA* p){    //Pode receber copia, mas sera usado ponteiro.
	return sizeof(PILHA) + sizeof(ELEMENTO)*tamanho(*p);   //Como ele espera receber uma copia, ele usa o asterisco no parametro para acessar o que tem dentro e copiar.
}

bool estaVazia(PILHA p){
	if(p.topo == NULL) return true;
	return false;
}

bool inserir (PILHA* p, REGISTRO reg){
	PONT novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->reg = reg;
	novo->prox = p->topo;
	p->topo = novo;
	return true;
}

bool excluir(PILHA* p, REGISTRO* reg){    //Nao pode receber copia, pois vai alterar topo, entao caso seja copia, altera topo, mas nao na pilha em si.
	if(p->topo == NULL) return false;
	PONT apagar = p->topo;
	*reg = apagar->reg;        //reg = &(apagar->reg);    Compila mas nao copia para o endereco de reg(ele cria uma var local e substitui)
	p->topo = p->topo->prox;
	free(apagar);
	return true;
}

void reinicializar(PILHA* p){
	PONT apagar, atual;
	atual = p->topo;
	while(atual){
		apagar = atual;
		atual = atual->prox;
		free(apagar);
	}
}

int main(){
	PILHA p1;        //Cria uma estrutura com um campo chamado topo.
	inicializar(&p1);
	tamanhoEmBytes(&p1);
	inserir(&p1, r1);
	/*...........*/
	REGISTRO r1;
	while(excluir(&p1,&r1)){
		printf("chave: %i\n", r1.chave);
	}
}