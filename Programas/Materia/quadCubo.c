#include <stdio.h>

//Lista Ligada

int quadCubo(int x, int* y){
    *y = x * x * x;
    return x*x;
}
int main(){
    int a = 3;
    int cubo,quad;   //Aloca as vari�veis que receber�o os n�meros da fun��o quadCubo.
    quad = quadCubo(a, &cubo);  //Armazena na vari�vel quad o quadrado que ser� retornado. E passando o endere�o da vari�vel cubo, voc� permite modificar dentro da fun��o o cubo pegando seu ponteiro.
    printf("%i, %i, %i \n", a, quad, cubo);
    return 0;
}
