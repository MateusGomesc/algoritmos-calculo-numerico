#include "lagrange.h"

double L(int quantPontos, double* xs, double* ys, int i, double x){
    int j;
    double numerador = 1, denominador = 1;

    for(j=0; j<quantPontos; j++){
        if(j != i){
            numerador *= (x - xs[j]);
            denominador *= (xs[i] - xs[j]);
        }
    }

    return (numerador / denominador);
}

double lagrange(int quantPontos, double* xs, double* ys, double x){
    int i;
    double pn = 0;

    for(i=0; i<quantPontos; i++)
        pn += ys[i] * L(quantPontos, xs, ys, i, x);
    return pn;
}
