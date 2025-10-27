#include "tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int error, i;
    double ak, bk, xk, epsilum, x;
    char functionString[100], signalCharacter;

    // Setando váriaveis da função
    te_variable vars[] = {{"x", &x}};

    printf("Método da bissecção\n\n");
    printf("Consulte a sintaxe da biblioteca math.h para injetar a função.\nColoque epsilum com a notacao de ponto flutuante.\nPrograma trabalhando com a precisao de 6 casas decimais apos a virgula.\n\n");

    // Recebendo parâmetros iniciais
    printf("f(x) = ");
    scanf(" %[^\n]", functionString);

    printf("ak = ");
    scanf("%lf", &ak);

    printf("bk = ");
    scanf("%lf", &bk);

    printf("Epsilum = ");
    scanf("%lf", &epsilum);

    // Compilando string para função matemática
    te_expr *expr = te_compile(functionString, vars, 1, &error);
    printf("\nAvaliando: \n\t%s\n", functionString);

    if(expr){
        printf("\n+---------------------------------------------------------------------------------------+\n");
        printf("|k\t ak\t\t xk\t\t bk\t\t f(ak)*f(xk)\t bk-ak\t\t|\n");
        for(i=0; fabs(bk - ak) > epsilum; i++){ // Realiza bloco até aproximação desejada
            // Encontra ponto médio do intervalo
            xk = (ak + bk) / 2;

            // Aplicando funções
            x = ak;
            const double fak = te_eval(expr);

            x = xk;
            const double fxk = te_eval(expr);

            // Verificação de mudança de sinal
            double signal = fak * fxk;

            // Formatação do sinal para a tabela
            if(signal < 0)
                signalCharacter = '-';
            if(signal > 0)
                signalCharacter = '+';
            if(signal == 0)
                signalCharacter = '=';


            printf("|%d\t %lf\t %lf\t %lf\t %c\t\t %lf\t|\n", i, ak, xk, bk, signalCharacter, fabs(bk-ak));

            // Modificação do intervalo
            if(signal < 0)
                bk = xk;
            if(signal > 0)
                ak = xk;
            if(signal == 0)
                break;
        }
        // Última linha da tabela
        xk = (ak + bk) / 2;
        printf("|%d\t %lf\t %lf\t %lf\t \t\t %lf\t|\n", i, ak, xk, bk, fabs(bk-ak));
        printf("+---------------------------------------------------------------------------------------+\n\n");

        printf("Valor aproximado de x: %lf\n", xk);
    }
    else{
        printf("\t%*s^\nError near here", error-1, "");
    }

    return 0;
}
