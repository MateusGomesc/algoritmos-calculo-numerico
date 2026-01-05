#include <stdio.h>
#include <stdlib.h>
#include "lagrange.h"
#include "newton.h"

int main()
{
    // Configuração do terminal para UTF-8
    system("chcp 65001 >nul");

    double *xs, *ys, x, res;
    int n, i, opcForma, grau;

    printf("Interpolacao Polinomial\n\n");
    printf("Certifique-se de ter o gnuplot instalado (http://www.gnuplot.info/).\n\n");

    // Recebendo informacoes iniciais
    printf("Forma:\n");
    printf("[1] - Lagrange\n");
    printf("[2] - Newton\n");
    printf("Opcao: ");
    scanf("%d", &opcForma);

    if(opcForma != 1 && opcForma != 2){
        printf("Opcao invalida!\n");
        exit(1);
    }

    printf("\n");

    printf("Quantidade de pontos: ");
    scanf("%d", &n);
    printf("\n");

    // Criando arrays para os pontos
    xs = (double*) malloc(sizeof(double) * n);
    ys = (double*) malloc(sizeof(double) * n);
    if(xs == NULL || ys == NULL){
        printf("Erro ao alocar memoria para as coordenadas.\n");
        exit(1);
    }

    for(i=0; i<n; i++){
        printf("Coordenada %d: ", i+1);
        scanf("%lf %lf", &xs[i], &ys[i]);
    }
    printf("\n");

    if(opcForma == 2){
        printf("Grau: ");
        scanf("%d", &grau);
    }

    printf("X alvo: ");
    scanf("%lf", &x);


    // Comunicando com o gnuplot
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if(gnuplot == NULL){
        printf("Gnuplot nao encontrado. Instale-o no site oficial.\n");
        exit(1);
    }

    // Configurando o gnuplot
    fprintf(gnuplot, "set title 'Forma de Lagrange'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set xlabel 'X'\n");
    fprintf(gnuplot, "set ylabel 'Y'\n");
    fprintf(gnuplot, "set key below\n");
    fprintf(gnuplot, "plot '-' with points pt 7 ps 1.5 lc rgb 'blue' title 'Pontos dados', \
                            '-' with lines lc rgb 'green' lw 2 title 'Polinomio', \
                            '-' with points pt 7 ps 2 lc rgb 'red' title 'Ponto calculado'\n");

    // Plotando os pontos principais
    for(i=0; i<n; i++){
        fprintf(gnuplot, "%lf %lf\n", xs[i], ys[i]);
    }
    fprintf(gnuplot, "e\n");

    // Plotando a curva considerando 100 pontos
    double passo = (xs[n-1] - xs[0]) / 100.00;
    for(double k = xs[0]; k <= (xs[n-1] + passo); k += passo){
        if(opcForma == 1)
            fprintf(gnuplot, "%lf %lf\n", k, lagrange(n, xs, ys, k));
        else
            fprintf(gnuplot, "%lf %lf\n", k, newton(n, xs, ys, k, grau, 0));
    }
    fprintf(gnuplot, "e\n");


    // Plotando o ponto resultado
    if(opcForma == 1)
        res = lagrange(n, xs, ys, x);
    else
        res = newton(n, xs, ys, x, grau, 1);
    printf("Y calculado: %lf\n", res);
    fprintf(gnuplot, "%lf %lf\n", x, res);
    fprintf(gnuplot, "e\n");

    pclose(gnuplot);
    free(xs);
    free(ys);

    return 0;
}
