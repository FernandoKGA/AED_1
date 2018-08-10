#include <stdio.h>
#include <malloc.h> //<stdlib.h> também pode ser usado.
int main(){
    int x[3];
    x[0] = 1;
    x[1] = 2;
    x[2] = 7;
    printf("x0: %i, x1: %i, x2: %i \n", x[0], x[1], x[2]);
    printf("&x: %p, x: %p, *x: %i \n", &x, x, *x);
    int* y = (int*)malloc(sizeof(int)*3);
    y[0]=4;
    y[1]=5;
    y[2]=6;
    printf("&y: %p, y: %p, *y: %i \n", &y, y, *y);  //y: %p vai mostrar o endereço de memória em que se localiza o arranjo alocado pelo malloc.
    y=(int*)x;
    printf("&y: %p, y: %p, *y: %i \n", &y, y, *y);
    return 0;
}
