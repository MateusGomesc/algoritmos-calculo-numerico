#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tinyexpr.h"

double derivada(te_expr *expr, double *x){
    double h = 1e-6;
    double temp = *x;
    *x = temp + h;
    double fxAddH = te_eval(expr);
    *x = temp - h;
    double fxMinusH = te_eval(expr);
    *x = temp;
    return (fxAddH - fxMinusH) / (2*h);
}

double newtonMethod(te_expr *expr, double *x, double epsilon){
    double er = 1;
    int i;

    printf("\n\n┌───────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ k\t xk\t\t f(xk)\t\t f'(xk)\t\t xk+1\t\t er\t\t│\n");
    printf("├───────────────────────────────────────────────────────────────────────────────────────┤\n");
    for(i=0; er > epsilon; i++){
        double fxk = te_eval(expr);
        double dfxk = derivada(expr, x);
        double xkNext = *x - (fxk / dfxk);
        er = fabs(xkNext - *x) / fabs(xkNext);
        printf("│ %d\t %lf\t %lf\t %lf\t %lf\t %lf\t│\n", i, *x, fxk, dfxk, xkNext, er);
        *x = xkNext;
    }
    printf("└───────────────────────────────────────────────────────────────────────────────────────┘\n\n");

    return *x;
}

int main()
{
    // Configuração do terminal para UTF-8
    system("chcp 65001 >nul");

    double x, epsilon;
    int error;
    char exprStr[200];

    printf("Metodo de Newton Para Zero de Funcoes\n\n");

    printf("Consulte a sintaxe da biblioteca math.h (https://petbcc.ufscar.br/math/) para injetar a função.\n");
    printf("Insira epsilon com a notação decimal.\n");
    printf("Sistema trabalhando com 6 casas decimais apos a virgula.\n\n");

    // Entrada de dados
    printf("f(x) = ");
    scanf(" %[^\n]", exprStr);

    printf("xk = ");
    scanf("%lf", &x);

    printf("Epsilon = ");
    scanf("%lf", &epsilon);

    // Compilando a função
    te_variable vars[] = {{"x", &x}};
    te_expr *expr = te_compile(exprStr, vars, 1, &error);

    printf("\nAvaliando... \n\n\t%s\n", exprStr);

    if(expr){
        printf("Valor aproximado para x: %lf\n", newtonMethod(expr, &x, epsilon));
    }
    else{
        printf("\t%*s^\nError near here", error-1, "");
    }


    te_free(expr);
    system("pause");
    return 0;
}
