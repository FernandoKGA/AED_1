#include <stdio.h>
#include <malloc.h>
typedef struct aux{
    int cpf;
    int idade;
    struct aux* conjuge;  //O ponteiro aux permite que ele direcione para a mesma estrutura uma estrutura repetida. O que não aconteceria normalmente.
}Pessoa;
typedef struct{
    Pessoa turma[66];
}TURMA;
void imprimirCPF(Pessoa p){
    if(p.conjuge != NULL){
        printf("CPF: %i x %i \n", p.cpf, p.conjuge->cpf);
    }
}
void trocar1(Pessoa p){
    p.idade++;
}
void trocar2(Pessoa* p){
    p->idade++;
}
void trocar3(Pessoa p){
    p.conjuge->idade++;  //No struct tem um endereço de conjuge, então alterando naquele p1, estamos acessando p2 diretamente pelo endereço.
}
int main(){
    Pessoa p1;
    Pessoa p2;
    p1.cpf = 310000;
    p1.idade = 36;

    p2.cpf = 290000;
    p2.idade = 34;

    p1.conjuge = &p2;
    p2.conjuge = &p1;
    imprimirCPF(p1);

    Pessoa solteira;
    solteira.cpf = 230.000;
    solteira.idade = 30;
    solteira.conjuge = NULL;
    printf("Solteira: %i %i %p\n",solteira.cpf,solteira.idade,solteira.conjuge);
    trocar1(solteira); //Passa SOLTEIRA e ela será copiada para o método como outra cópia, não alterando o seu valor.(Pois o método será excluído.)
    trocar2(&solteira); //Recebe o ENDEREÇO e assim altera SOLTEIRA.
    trocar3(p1);
    printf("Solteira: %i %i %p\n",solteira.cpf,solteira.idade,solteira.conjuge);
    return 0;
}
