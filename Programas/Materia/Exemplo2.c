#include <stdio.h>
#include <malloc.h>
int main(){
int n = 10;
int i;
printf("Tamanho do int: %i \n", sizeof(int));
int* arranjo = (int*) malloc(sizeof(int)*n);  //Aloca uma parte da mem�ria e devolve um endere�o de mem�ria indicando para o vazio, e o typecast coloca como ponteiro de inteiro para arranjo.
for(i=0;i<n;i++) arranjo[i] = 2*i;
int* pos = arranjo;  //Ponteiro para inteiro que recebe o endere�o de arranjo.
for(i=0;i<n;i++){
    printf("Posicao: %p, Valor: %i \n", pos, *pos); //*Pos retorna um valor que est� dentro deste local dentro da memoria.
    pos++;
}
free(arranjo);

return 0;
}
