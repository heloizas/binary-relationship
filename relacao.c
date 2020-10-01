#include <stdio.h>

#define MAXTAM 100

typedef struct {
    int x;
    int y;
    int xfecho;
    int yfecho;
} Tuple;

void printMatrix(int Matrix[][MAXTAM], int n, int m, int matrixName) {
	int i, j;
	printf("\n");
    //i e j igual a 1 para não imprimir coluna e linha com índice 0
	for(i=matrixName; i<n; i++) {
		for(j=matrixName; j<m; j++) { 
			printf("%d ", Matrix[i][j]);
		}
		printf("\n");
	}
    printf("\n");
}

void writeFile(char check, int count, Tuple values[], char text[]) {
    printf("%s: %c", text, check);
    if (check == 'F'){
        printf("\n");
    }
    for (int i=0; i<count; i++){
        printf("(%d,%d); ", values[i].x, values[i].y);
    }
    printf("\n");
}

int main() {
    int matrixSize, matrixName, maxName, n, m, i, j, first, second, 
        contadorref = 0, contadorirref = 0, contadorsimetrica = 0, 
        contadorantisimetrica = 0, 
        Matrix[MAXTAM][MAXTAM];
    char linha[MAXTAM];
    char reflexiva = 'F';
    char irreflexiva = 'F';
    char simetrica = 'F';
    char antisimetrica = 'V';
    char assimetrica = 'F';
    char transitiva = 'V';
    char relacaoequivalencia = 'F';
    char relacaoordempacial = 'F';

    FILE *file;

    //Entrada e validação
    file = fopen("entrada.txt","r");
    if (file == NULL) {
        printf("Arquivo não encontrado!\n");
        return 0;
    }
    //Pega o tamanho e o nome da matriz
    fscanf(file, "%d %d", &matrixSize, &matrixName);
    //Pega o valor do último nome
    maxName = matrixName+matrixSize-1;
    //Pois o vetor começa na posição 0. Sem acrescentar o 1, as últimas relações não apareceria
    maxName = maxName + 1;
    //Preenchimento da matriz
	n=maxName; m=maxName;

    //Preenchimento da matriz
    while(fgets(linha, 100, file) != NULL) {
        fscanf(file, "%i %i", &first, &second);
        Matrix[first][second] = 1;
    }

    //REFLEXIVA
    Tuple faltaReflexiva[n];
    int faltaReflexivaContagem = 0;
    for(i=matrixName; i<n; i++) {
        if(Matrix[i][i]) {
            contadorref += 1;
        }
        else {
            faltaReflexiva[faltaReflexivaContagem].x = i;
            faltaReflexiva[faltaReflexivaContagem].y = i;
            faltaReflexivaContagem++;
        }
    }
    if (contadorref == matrixSize) {
        reflexiva = 'V';
    }

    writeFile(reflexiva, faltaReflexivaContagem, faltaReflexiva, "Reflexiva");

    //IRREFLEXIVA
    Tuple faltaIrreflexiva[n];
    int faltaIrreflexivaContagem = 0;
    for(i=matrixName; i<n; i++) {
        if(!Matrix[i][i]) {
            contadorirref += 1;
        }
        else {
            faltaIrreflexiva[faltaIrreflexivaContagem].x = i;
            faltaIrreflexiva[faltaIrreflexivaContagem].y = i;
            faltaIrreflexivaContagem++;
        }
    }
    if (contadorirref == matrixSize) {
        irreflexiva = 'V';
    }

    writeFile(irreflexiva, faltaIrreflexivaContagem, faltaIrreflexiva, "Irreflexiva");

    //SIMÉTRICA
    Tuple faltaSimetrica[n];
    int faltaSimetricaContagem = 0;
    for(i=matrixName; i<n; i++) {
		for(j=matrixName; j<m; j++) {
			if(Matrix[i][j] == Matrix[j][i]) {
                contadorsimetrica += 1;
            }
            else if((Matrix[j][i]) && (!Matrix[i][j])) {
                faltaSimetrica[faltaSimetricaContagem].x = i;
                faltaSimetrica[faltaSimetricaContagem].y = j;
                faltaSimetricaContagem++;
            }
		}
	}
    if (contadorsimetrica == matrixSize*matrixSize) {
        simetrica = 'V';
    }

    writeFile(simetrica, faltaSimetricaContagem, faltaSimetrica, "Simétrica");

    //ANTI-SIMÉTRICA
    Tuple faltaAntiSimetrica[n];
    int faltaAntiSimetricaContagem = 0;
    for(i=matrixName; i<n; i++) {
		for(j=matrixName; j<m; j++) {
			if(Matrix[i][j] == Matrix[j][i]) {
                if ((i!=j) && (Matrix[i][j])){
                    antisimetrica = 'F';
                    faltaAntiSimetrica[faltaAntiSimetricaContagem].x = i;
                    faltaAntiSimetrica[faltaAntiSimetricaContagem].y = j;
                    faltaAntiSimetricaContagem++;
                }
            }
		}
	}
    
    writeFile(antisimetrica, faltaAntiSimetricaContagem, faltaAntiSimetrica, "Anti-simétrica");

    //ASSIMÉTRICA
    //É assimétrica se for irreflexiva e anti-simétrica
    if ((irreflexiva == 'V') && (antisimetrica == 'V')) {
        assimetrica = 'V';
    }

    printf("Assimétrica: %c\n", assimetrica);

    //TRANSITIVA
    Tuple faltaTransitiva[n];
    int faltaTransitivaContagem = 0;
    for (int i=matrixName; i<n; i++){
        for (int j=matrixName; j<n; j++){
            if (Matrix[i][j]){
                for (int z=matrixName; z<n; z++){
                    if (Matrix[j][z] && !Matrix[i][z]) {
                        transitiva = 'F';
                        faltaTransitiva[faltaTransitivaContagem].x = i;
                        faltaTransitiva[faltaTransitivaContagem].y = z;
                        faltaTransitivaContagem++;
                   }
                }
            }
        }
    }

    // TRANSITIVA SEM DUPLICIDADE
    Tuple faltaTransitivaSemDuplicidade[faltaTransitivaContagem];
    int faltaTransitivaSemDuplicidadeContagem = 0;
    int insere = 1;
    for (int i = 0; i < faltaTransitivaContagem; i++){
        for (int j = 0; j < faltaTransitivaSemDuplicidadeContagem; j++){
            if (faltaTransitiva[i].x == faltaTransitivaSemDuplicidade[j].x && faltaTransitiva[i].y == faltaTransitivaSemDuplicidade[j].y){
                insere = 0;
            }
        }
        if (insere){
            faltaTransitivaSemDuplicidade[faltaTransitivaSemDuplicidadeContagem] = faltaTransitiva[i];
            faltaTransitivaSemDuplicidadeContagem++;
        }
        insere = 1;
    }

    writeFile(transitiva, faltaTransitivaSemDuplicidadeContagem, faltaTransitivaSemDuplicidade, "Transitiva");

    //FECHO TRANSITIVO
    Tuple fechoTransitivo[n];
    int fechoTransitivoContagem = 0;
    for(i=matrixName; i<n; i++) {
		for(j=matrixName; j<m; j++) {
			if(Matrix[i][j]){
                fechoTransitivo[fechoTransitivoContagem].xfecho = i;
                fechoTransitivo[fechoTransitivoContagem].yfecho = j;
                fechoTransitivoContagem++;
            }
		}
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
    printf("Relação de equivalência: %c\n", relacaoequivalencia);
    printf("Relação de ordem parcial: %c", relacaoordempacial);
    printf("\nFecho transitivo da relação: ");
    for (int i = 0; i < fechoTransitivoContagem; i++){
        printf("(%d,%d); ", fechoTransitivo[i].xfecho, fechoTransitivo[i].yfecho);
    }
    for (int i = 0; i < faltaTransitivaSemDuplicidadeContagem; i++){
        printf("(%d,%d); ", faltaTransitivaSemDuplicidade[i].x, faltaTransitivaSemDuplicidade[i].y);
    }
    printf("\n");
    fclose(file);
    return 0;
}