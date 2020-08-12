#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTAM 100

void printmatrix(int M[][MAXTAM], int n, int m) {
	int i, j;
	printf("\n");
    //i e j igual a 0 para não imprimir coluna e linha com índice 0
	for(i=1; i<n; i++) {
		for(j=1; j<m; j++){ 
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
    printf("\n");
}

int main() {
    int size, n, m, i, j, first, second, contadorref = 0, M[MAXTAM][MAXTAM];
    char linha[MAXTAM];
    char reflexiva = 'F';
    char irreflexiva = 'F';

    FILE *file, *saida;

    //Entrada e validação
    file = fopen("relacao.txt","r");
    if (file == NULL) {
        printf("Arquivo não encontrado!\n");
        return 0;
    }

    //Pega o tamanho da matriz, primeiro dígito do arquivo
    fscanf(file, "%d", &size);

    //Pois o vetor começa na posição 0. Sem acrescentar o 1, últimas relações não apareceria
    size = size + 1;

    //Preenchimento da matriz
	n=size; m=size;

    //Preenche com 0
	// for(i=0; i<n; i++){
	// 	for(j=0; j<m; j++) {
	// 		M[i][j] = 0;
	// 	}
	// }

    while(fgets(linha, 100, file) != NULL) {
        fscanf(file, "%i %i", &first, &second);
        // printf("%i %i\n", first, second);
        M[first][second] = 1;
    }

	printmatrix(M, n, m);

    //Verificação Reflexiva
    for(i=1; i<n; i++) {
        if(M[i][i] == 1){
            contadorref += 1;
        }
    }
    if (contadorref == size - 1){
        reflexiva = 'V';
    }
    
    //Verificação das relações encontradas
    // for(i=0; i<n; i++) {
	// 	for(j=0; j<m; j++) {
	// 		if(M[i][j] == 1){
    //             printf("Tem relação: %i %i\n", i, j);
    //         }
	// 	}
	// }

    //Saída
    saida = fopen("saida.txt", "w");
    fprintf(saida, "Propriedades:\n1. Reflexiva: %c\n2. Irreflexiva:\n3. Simétrica:\n4. Anti-simétrica:\n5. Assimétrica:\n6. Transitiva:\nRelação de equivalência:\nRelação de ordem parcial:\nFecho transitivo da relação: %d", reflexiva, size);

    fclose(file);
    fclose(saida);
    return 0;
}