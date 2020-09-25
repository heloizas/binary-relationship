#include <stdio.h>

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

void writeFile(FILE *saida, char check, int count, Tupla values[], char text[]) {
    fprintf(saida, "%s: %c", text, check);
    if (check == 'F'){
        fprintf(saida, "\n");
    }
    for (int i = 0; i < count; i++){
        fprintf(saida, "(%d,%d); ", values[i].x, values[i].y);
    }
    fprintf(saida, "\n");
}

// void readFile(FILE *file, int size, int name, int maxname, char linha[], int first, int second, int Matriz[][MAXTAM], int n, int m){
//     //Entrada e validação
//     file = fopen("relacao.txt","r");
//     if (file == NULL) {
//         printf("Arquivo não encontrado!\n");
//         return;
//     }
//     //Pega o tamanho e o nome da matriz
//     fscanf(file, "%d %d", &size, &name);
//     //Pega o valor do último nome
//     maxname = name+size-1;
//     //Pois o vetor começa na posição 0. Sem acrescentar o 1, as últimas relações não apareceria
//     maxname = maxname + 1;
//     //Preenchimento da matriz
// 	n=maxname; m=maxname;
//     while(fgets(linha, 100, file) != NULL) {
//         fscanf(file, "%i %i", &first, &second);
//         Matriz[first][second] = 1;
//     }
// }

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
    saida = fopen("saida.txt", "w");

    //REFLEXIVA
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

    writeFile(saida, reflexiva, faltaReflexivaContagem, faltaReflexiva, "Reflexiva");

    //IRREFLEXIVA
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

    writeFile(saida, irreflexiva, faltaIrreflexivaContagem, faltaIrreflexiva, "Irreflexiva");

    //SIMÉTRICA
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

    writeFile(saida, simetrica, faltaSimetricaContagem, faltaSimetrica, "Simétrica");

    //ANTI-SIMÉTRICA
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
    
    writeFile(saida, antisimetrica, faltaAntiSimetricaContagem, faltaAntiSimetrica, "Anti-simétrica");

    //ASSIMÉTRICA
    //É assimétrica se for irreflexiva e anti-simétrica
    if ((irreflexiva == 'V') && (antisimetrica == 'V')) {
        assimetrica = 'V';
    }

    fprintf(saida, "Assimétrica: %c\n", assimetrica);
    
    //TRANSITIVA
    Tupla faltaTransitiva[n];
    int faltaTransitivaContagem = 0;
    for (int i=name; i<n; i++){
        for (int j=name; j<n; j++){
            if (Matriz[i][j]){
                for (int z=name; z<n; z++){
                    if (Matriz[j][z] && !Matriz[i][z]) {
                        transitiva = 'F';
                        faltaTransitiva[faltaTransitivaContagem].x = i;
                        faltaTransitiva[faltaTransitivaContagem].y = z;
                        faltaTransitivaContagem++;
                    }
                }
            }
        }
    }

    writeFile(saida, transitiva, faltaTransitivaContagem, faltaTransitiva, "Transitiva");

    //FECHO TRANSITIVO
    Tupla fechoTransitivo[n];
    int fechoTransitivoContagem = 0;
    for(i=name; i<n; i++) {
		for(j=name; j<m; j++) {
			if(Matriz[i][j] == 1){
                fechoTransitivo[fechoTransitivoContagem].x = i;
                fechoTransitivo[fechoTransitivoContagem].y = j;
                fechoTransitivoContagem++;
            }
		}
    }

    for (int i = 0; i < faltaTransitivaContagem; i++){
        printf("(%d,%d); ", faltaTransitiva[i].x, faltaTransitiva[i].y);
    }

    //EQUIVALÊNCIA
    if ((reflexiva == 'V') && (simetrica == 'V') && (transitiva == 'V')) {
        relacaoequivalencia = 'V';
    }

    //ORDEM PARCIAL
    if ((reflexiva == 'V') && (transitiva == 'V') && (antisimetrica == 'V')) {
        relacaoordempacial = 'V';
    }

    //Saída
    fprintf(saida, "Relação de equivalência: %c\n", relacaoequivalencia);
    fprintf(saida, "Relação de ordem parcial: %c", relacaoordempacial);
    fprintf(saida, "\nFecho transitivo da relação: ");
    for (int i = 0; i < fechoTransitivoContagem; i++){
        fprintf(saida, "(%d,%d); ", fechoTransitivo[i].x, fechoTransitivo[i].y);
    }
    for (int i = 0; i < faltaTransitivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaTransitiva[i].x, faltaTransitiva[i].y);
    }
    fclose(saida);
    fclose(file);
    return 0;
}