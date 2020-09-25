#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXTAM 100

typedef struct
{
    int x;
    int y;
} Tupla;

void printmatrix(int M[][MAXTAM], int n, int m, int name) {
	int i, j;
	printf("\n");
    //i e j igual a 1 para não imprimir coluna e linha com índice 0
	for(i=name; i<n; i++) {
		for(j=name; j<m; j++) { 
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
    printf("\n");
}

int main() {
    int size, name, maxname, n, m, i, j, first, second, 
        contadorref = 0, contadorirref = 0, contadorsimetrica = 0, 
        contadorantisimetrica = 0, 
        M[MAXTAM][MAXTAM];
    char linha[MAXTAM];
    char reflexiva = 'F';
    char irreflexiva = 'F';
    char simetrica = 'F';
    char antisimetrica = 'V';
    char assimetrica = 'F';
    char transitiva = 'F';
    char relacaoequivalencia = 'F';
    char relacaoordempacial = 'F';

    FILE *file, *saida;

    //Entrada e validação
    file = fopen("relacao.txt","r");
    if (file == NULL) {
        printf("Arquivo não encontrado!\n");
        return 0;
    }

    //Pega o tamanho e o nome da matriz
    fscanf(file, "%d %d", &size, &name);

    //Pega o valor do último nome
    maxname = name+size-1;

    //Pois o vetor começa na posição 0. Sem acrescentar o 1, as últimas relações não apareceria
    maxname = maxname + 1;

    //Preenchimento da matriz
	n=maxname; m=maxname;

    while(fgets(linha, 100, file) != NULL) {
        fscanf(file, "%i %i", &first, &second);
        M[first][second] = 1;
    }

	// printmatrix(M, n, m, name);

    //Verificação Reflexiva
    Tupla faltaReflexiva[n];
    int faltaReflexivaContagem = 0;
    for(i=name; i<n; i++) {
        if(M[i][i] == 1) {
            contadorref += 1;
        }
        else {
            faltaReflexiva[faltaReflexivaContagem].x = i;
            faltaReflexiva[faltaReflexivaContagem].y = i;
            faltaReflexivaContagem++;
        }
    }
    if (contadorref == size) {
        reflexiva = 'V';
    }

    //Verificação Irreflexiva
    Tupla faltaIrreflexiva[n];
    int faltaIrreflexivaContagem = 0;
    for(i=name; i<n; i++) {
        if(M[i][i] == 0) {
            contadorirref += 1;
        }
        else {
            faltaIrreflexiva[faltaIrreflexivaContagem].x = i;
            faltaIrreflexiva[faltaIrreflexivaContagem].y = i;
            faltaIrreflexivaContagem++;
        }
    }
    if (contadorirref == size) {
        irreflexiva = 'V';
    }

    //Verificação Simétrica
    Tupla faltaSimetrica[n];
    int faltaSimetricaContagem = 0;
    for(i=name; i<n; i++) {
		for(j=name; j<m; j++) {
			if(M[i][j] == M[j][i]) {
                contadorsimetrica += 1;
            }
            else if((M[j][i] == 1) && (M[i][j] == 0)) {
                faltaSimetrica[faltaSimetricaContagem].x = i;
                faltaSimetrica[faltaSimetricaContagem].y = i;
                faltaSimetricaContagem++;
            }
		}
	}
    if (contadorsimetrica == size*size) {
        simetrica = 'V';
    }

    //Verificação Anti-Simétrica
    Tupla faltaAntiSimetrica[n];
    int faltaAntiSimetricaContagem = 0;
    for(i=name; i<n; i++) {
		for(j=name; j<m; j++) {
			if(M[i][j] == M[j][i]) {
                if ((i!=j) && (M[i][j] == 1)){
                    antisimetrica = 'F';
                    faltaAntiSimetrica[faltaAntiSimetricaContagem].x = i;
                    faltaAntiSimetrica[faltaAntiSimetricaContagem].y = j;
                    faltaAntiSimetricaContagem++;
                    // printf("M[i][j]: %d\n", M[i][j]);
                    // printf("M[j][i]: %d\n", M[j][i]);
                    // printf("i, j: %i %i\n\n", i, j);
                    // printf("contadorantisimetrica: %d\n", contadorantisimetrica);
                }
            }
		}
	}
    //Verificação Assimétrica
    //É assimétrica se for irreflexiva e anti-simétrica
    if ((irreflexiva == 'V') && (antisimetrica == 'V')) {
        assimetrica = 'V';
    }

    //Verificação Transitiva
    
    //Relação de Equivalência
    if ((reflexiva == 'V') && (simetrica == 'V') && (transitiva == 'V')) {
        relacaoequivalencia = 'V';
    }
    //Relação de ordem parcial
    if ((reflexiva == 'V') && (transitiva == 'V') && (antisimetrica == 'V')) {
        relacaoordempacial = 'V';
    }
    // Verificação das relações encontradas
    // for(i=0; i<n; i++) {
	// 	for(j=0; j<m; j++) {
	// 		if(M[i][j] == 1){
    //             printf("Tem relação: %i %i\n", i, j);
    //         }
	// 	}
	// }

    //Saída
    saida = fopen("saida.txt", "w");
    fprintf(saida, "Reflexiva: %c \n", reflexiva);
    for (int i = 0; i < faltaReflexivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaReflexiva[i].x, faltaReflexiva[i].y);
    }
    fprintf(saida, "\nIrreflexiva: %c\n", irreflexiva);
    for (int i = 0; i < faltaIrreflexivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaIrreflexiva[i].x, faltaIrreflexiva[i].y);
    }
    fprintf(saida, "\nSimétrica: %c\n", simetrica);
    for (int i = 0; i < faltaSimetricaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaSimetrica[i].x, faltaSimetrica[i].y);
    }
    fprintf(saida, "\nAnti-simétrica: %c\n", antisimetrica);
    for (int i = 0; i < faltaAntiSimetricaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaAntiSimetrica[i].x, faltaAntiSimetrica[i].y);
    }
    fprintf(saida, "\nAssimétrica: %c\n", assimetrica);
    fprintf(saida, "\nTransitiva: to-do\n");
    fprintf(saida, "\nRelação de equivalência: to-do");
    fprintf(saida, "\nRelação de ordem parcial: to-do");
    fprintf(saida, "\nFecho transitivo da relação: to-do");
    
    fclose(file);
    fclose(saida);

    return 0;
}