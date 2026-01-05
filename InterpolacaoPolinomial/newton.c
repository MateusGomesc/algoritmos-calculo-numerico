#include "newton.h"
#include<stdio.h>
#include<stdlib.h>

void encontrarMelhorIntervalor(double* pontos, int quantPontos, int n, double x, int* inicio, int* fim){
    double distancia, menorDistancia;

    int inicioTemp = 0;
    int fimTemp = n-1;
    menorDistancia = pontos[fimTemp] - pontos[inicioTemp];
    *inicio = inicioTemp;
    *fim = fimTemp;
    do{
        distancia = pontos[fimTemp] - pontos[inicioTemp];

        if(x >= pontos[inicioTemp] && x <= pontos[fimTemp] && distancia < menorDistancia){
            *inicio = inicioTemp;
            *fim = fimTemp;
        }
        inicioTemp++;
        fimTemp = inicioTemp + n - 1;
    }while(fimTemp < quantPontos);
}

void mostrarTDD(double** m, int n){
    int i, j;

    printf("\n");
    printf("TDD\n┌");
    for(i=0; i<n+1; i++)
        printf("─────────");
    printf("─┐\n");

    for(i=0; i<n; i++){
            printf("│ ");
        for(j=0; j<n+1; j++){
            printf("%lf ", m[i][j]);
        }
        printf("│\n");
    }

    printf("└");
    for(i=0; i<n+1; i++)
        printf("─────────");
    printf("─┘\n\n");
}

double* tdd(double* xs, double* ys, int n, int inicio, int showTDD){
    double **m, *res;
    int i, j;

    // Criando matriz na memoria
    m = (double**) malloc(sizeof(double) * n);
    if(m == NULL){
        printf("Erro ao criar primeira dimensao da TDD.\n");
        exit(1);
    }

    for(i=0; i<n+1; i++){
        m[i] = (double*) malloc(sizeof(double) * n);
        if(m[i] == NULL){
            printf("Erro ao criar segunda dimensao da TDD.\n");
            exit(1);
        }
    }

    // Setando as duas primeiras colunas
    for(i=0; i<n; i++){
        m[i][0] = xs[inicio];
        m[i][1] = ys[inicio];
        inicio++;
    }

    // Calculando as outras posicoes
    int cont = 1;
    for(j=2; j<=n; j++){
        for(i=0; i<n-(j-1); i++){
            m[i][j] = (m[i+1][j-1] - m[i][j-1]) / (m[i+j-1][0] - m[i][0]);
        }
        cont++;
    }

    // Mostra TDD
    if(showTDD){
        mostrarTDD(m, n);
    }

    // Monta array de coeficientes
    res = (double*) calloc(sizeof(double), n);
    if(res == NULL){
        printf("Erro ao alocar memoria para array de resposta.\n");
        exit(1);
    }

    for(i=0, j=1; i<n; i++, j++)
        res[i] = m[0][j];


    // Liberando matriz da memoria
    for(i=0; i<n+1; i++){
        free(m[i]);
    }
    free(m);

    return res;
}

double polinomio(double* xs, double* coeficientes, double x, int n){
    double soma = coeficientes[0], multi=1;
    int i, j;

    for(i=1; i<n; i++){
        for(j=0; j<i; j++){
            multi *= (x - xs[j]);
        }
        soma += multi * coeficientes[i];
    }

    return soma;
}

double newton(int quantPontos, double* xs, double* ys, double x, int grau, int showTDD){
    int inicio, fim;
    double* coeficientes;

    encontrarMelhorIntervalor(xs, quantPontos, grau+1, x, &inicio, &fim);
    coeficientes = tdd(xs, ys, grau+1, inicio, showTDD);
    return polinomio(xs, coeficientes, x, grau+1);
}
