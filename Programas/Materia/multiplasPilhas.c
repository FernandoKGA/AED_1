#define ERRO -1
#define MAX 50
#define NP 5
#define true 1
#define false 0
typedef int TIPOCHAVE;

typedef int bool;

typedef struct{
    TIPOCHAVE chave;
    int base[NP+1];
    int topo[NP+1];
}PM;

//Cada fila ocupa um espaço de MAX/NP.
//Pilha vazia se topo == base.

void inicializar(PM* p){
    int x;
    for(x = 0;x <= NP; x++){
        p->topo[x] = x * MAX/NP -1;
        p->base[x] = p->topo[x];
    }
}

int tamanhoK(PM* p, int K){
    return p->topo[K]-p->base[K];
}

int tamanhoTotal(PM* p){
    int tam = 0;
    int x;
    for(x = 0, x <= NP; x++){
        tam += tamanhoK(p, x);
    }
    return tam;
}

bool popK(PM* p, TIPOCHAVE* ch, int K){ //POP retira da pila.
    if(p->topo[K] == p->base[K]) return false;
    *ch = p->A[p->topo[K]];
    p->topo[K]--;
    return true;
}

bool pilhaKcheia(PM* p, int K){
    if(p->topo[K] == p->base[K+1]) return true;
    else return false;
}

bool pushK(PM* p,TIPOCHAVE ch, int K){    //Inserir
    int x;
    if(pilhaKcheia(p,K)){
        for(x = NP-1;x > K;x--){
            paraDireita(p, x);
        }
        if(pilhaKcheia(p, K)){
            for(x = 1;x <= K; x++){
                paraEsquerda(p, x);
            }
        }
        if(pilhaKcheia(p, K)) return false;
    }
    p->topo[K]++;
    p->A[p->topo[K]] = ch;
    return true;
}

bool paraDireita(PM* p, int K){
    int x;
    if(pilhaKcheia(p, K)) return false;
    for(x = p->topo[K];x>p->base[K]; x--){
        p->A[x+1] = p->A[x];
    }
    p->topo[K]++;
    p->base[K]++;
    return true;
}

bool paraEsquerda(PM* p, int K){
    int x;
    if(pilhaKcheia(p, K)) return false;
    for(x = p->base[K+1];x<=p->base[K]; x++){
        p->A[x-1] = p->A[x];
    }
    p->topo[K]--;
    p->base[K]--;
    return true;
}


int main(){
    PM p1;
    inicializar(&p1);
    TIPOCHAVE chave1;
    popk(&p,&chave1,k);
}