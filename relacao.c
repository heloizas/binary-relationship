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

void printmatrix(int Matriz[][MAXTAM], int n, int m, int name) {
	int i, j;
	printf("\n");
    //i e j igual a 1 para não imprimir coluna e linha com índice 0
	for(i=name; i<n; i++) {
		for(j=name; j<m; j++) { 
			printf("%d ", Matriz[i][j]);
		}
		printf("\n");
	}
    printf("\n");
}

int main() {
    int size, name, maxname, n, m, i, j, first, second, 
        contadorref = 0, contadorirref = 0, contadorsimetrica = 0, 
        contadorantisimetrica = 0, 
        Matriz[MAXTAM][MAXTAM];
    char linha[MAXTAM];
    char reflexiva = 'F';
    char irreflexiva = 'F';
    char simetrica = 'F';
    char antisimetrica = 'V';
    char assimetrica = 'F';
    char transitiva = 'V';
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
        Matriz[first][second] = 1;
    }

	// printmatrix(M, n, m, name);

    //Verificação Reflexiva
    Tupla faltaReflexiva[n];
    int faltaReflexivaContagem = 0;
    for(i=name; i<n; i++) {
        if(Matriz[i][i] == 1) {
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
        if(Matriz[i][i] == 0) {
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
			if(Matriz[i][j] == Matriz[j][i]) {
                contadorsimetrica += 1;
            }
            else if((Matriz[j][i] == 1) && (Matriz[i][j] == 0)) {
                faltaSimetrica[faltaSimetricaContagem].x = i;
                faltaSimetrica[faltaSimetricaContagem].y = j;
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
			if(Matriz[i][j] == Matriz[j][i]) {
                if ((i!=j) && (Matriz[i][j] == 1)){
                    antisimetrica = 'F';
                    faltaAntiSimetrica[faltaAntiSimetricaContagem].x = i;
                    faltaAntiSimetrica[faltaAntiSimetricaContagem].y = j;
                    faltaAntiSimetricaContagem++;
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
    Tupla faltaTransitiva[n];
    int faltaTransitivaContagem = 0;
    for (int i=name; i < n; i++){
        for (int j=name; j < m; j++){
            for (int k=name; k < n; k++){
                if (Matriz[i][j] && Matriz[j][k] && !Matriz[i][k]){
                    transitiva = 'F';
                    faltaTransitiva[faltaTransitivaContagem].x = i;
                    faltaTransitiva[faltaTransitivaContagem].y = k;
                    faltaTransitivaContagem++;
                    printf("Para ser Transitiva: (%d,%d);\n", j,i);
                }
            }
        }
    }
    
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
	// 		if(Matriz[i][j] == 1){
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
    fprintf(saida, "\nAssimétrica: %c", assimetrica);
    fprintf(saida, "\nTransitiva: %c\n", transitiva);
    for (int i = 0; i < faltaTransitivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaTransitiva[i].x, faltaTransitiva[i].y);
    }
    fprintf(saida, "\nRelação de equivalência: %c", relacaoequivalencia);
    fprintf(saida, "\nRelação de ordem parcial: %c", relacaoordempacial);
    fprintf(saida, "\nFecho transitivo da relação: to-do");
    
    fclose(file);
    fclose(saida);

    return 0;
}