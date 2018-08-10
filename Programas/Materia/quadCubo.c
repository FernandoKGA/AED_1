#include <stdio.h>

//Lista Ligada

int quadCubo(int x, int* y){
    *y = x * x * x;
    return x*x;
}
int main(){
    int a = 3;
    int cubo,quad;   //Aloca as variáveis que receberão os números da função quadCubo.
    quad = quadCubo(a, &cubo);  //Armazena na variável quad o quadrado que será retornado. E passando o endereço da variável cubo, você permite modificar dentro da função o cubo pegando seu ponteiro.
    printf("%i, %i, %i \n", a, quad, cubo);
    return 0;
}
