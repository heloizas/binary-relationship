#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXTAM 100

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
        contadorantisimetrica = 0, contadorassimetrica = 0, 
        M[MAXTAM][MAXTAM];
    char linha[MAXTAM];
    char reflexiva = 'F';
    char irreflexiva = 'F';
    char simetrica = 'F';
    char antisimetrica = 'F';
    char assimetrica = 'F';

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

    //Pois o vetor começa na posição 0. Sem acrescentar o 1, últimas relações não apareceria
    maxname = maxname + 1;

    //Preenchimento da matriz
	n=maxname; m=maxname;

    while(fgets(linha, 100, file) != NULL) {
        fscanf(file, "%i %i", &first, &second);
        M[first][second] = 1;
    }

	printmatrix(M, n, m, name);

    //Verificação Reflexiva
    for(i=name; i<n; i++) {
        if(M[i][i] == 1) {
            contadorref += 1;
        }
        else {
            // printf("Para ser reflexiva: (%d,%d);\n", i,i);
        }
    }
    if (contadorref == size) {
        reflexiva = 'V';
    }
    
    //Verificação Irreflexiva
    for(i=name; i<n; i++) {
        if(M[i][i] == 0) {
            contadorirref += 1;
        }
        else {
            // printf("Para ser Irreflexiva: (%d,%d);\n", i,i);
        }
    }
    if (contadorirref == size) {
        irreflexiva = 'V';
    }

    //Verificação Simétrica
    for(i=name; i<n; i++) {
		for(j=name; j<m; j++) {
			if(M[i][j] == M[j][i]) {
                contadorsimetrica += 1;
            }
            else if((M[j][i] == 1) && (M[i][j] == 0)) {
                // printf("Para ser Simétrica: (%d,%d);\n", i,j);
            }
		}
	}
    if (contadorsimetrica == size*size) {
        simetrica = 'V';
    }

     //Verificação Anti-Simétrica
    // for(i=name; i<n; i++) {
	// 	for(j=name; j<m; j++) {
	// 		if(M[i][j] == M[j][i]) {
    //             contadorantisimetrica += 1;
    //         }
    //         else if((M[j][i] == 1) && (M[i][j] == 0)) {
    //             // printf("Para ser Simétrica: (%d,%d);\n", i,j);
    //         }
	// 	}
	// }
    // if (contadorsimetrica == size*size) {
    //     antisimetrica = 'V';
    // }

    //Verificação Assimétrica
    //É assimétrica se for irreflexiva e anti-simétrica
    for(i=name; i<n; i++) {
		for(j=name; j<m; j++) {
			if(M[i][j] != M[j][i]) {
                contadorassimetrica += 1;
            }
		}
	}
    if (contadorassimetrica == size*size) {
        assimetrica = 'V';
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
    fprintf(saida, "Reflexiva: %c\nIrreflexiva: %c\nSimétrica: %c\nAnti-simétrica: to-do %c\nAssimétrica: %c\nTransitiva:\nRelação de equivalência:\nRelação de ordem parcial:\nFecho transitivo da relação:", reflexiva, irreflexiva, simetrica, antisimetrica, assimetrica);

    fclose(file);
    fclose(saida);
    return 0;
}