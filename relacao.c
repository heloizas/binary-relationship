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
    
    //TRANSITIVA
    Tupla faltaTransitiva[n];
    int faltaTransitivaContagem = 0;
    for (int i=name; i<n; i++){
        for (int j=name; j<n; j++){
            for (int k=name; k<n; k++){
                if (Matriz[i][j] && Matriz[j][k] && !Matriz[i][k]){
                    transitiva = 'F';
                    faltaTransitiva[faltaTransitivaContagem].x = i;
                    faltaTransitiva[faltaTransitivaContagem].y = k;
                    faltaTransitivaContagem++;
                }
            }
        }
    }

    // TRANSITIVA (DUPLICIDADE)
    // Tupla faltaTransitivaSemDuplicidade[faltaTransitivaContagem];
    // int faltaTransitivaSemDuplicidadeContagem = 0;
    // int insere = 1;
    // for (int i=name; i < faltaTransitivaContagem; i++){
    //     for (int j=name; j < faltaTransitivaSemDuplicidadeContagem; j++){
    //         if (faltaTransitiva[i].x == faltaTransitivaSemDuplicidade[j].x && faltaTransitiva[i].y == faltaTransitivaSemDuplicidade[j].y){
    //             insere = 0;
    //         }
    //     }
    //     if (insere){
    //         faltaTransitivaSemDuplicidade[faltaTransitivaSemDuplicidadeContagem] = faltaTransitiva[i];
    //         faltaTransitivaSemDuplicidadeContagem++;
    //     }
    //     insere = 1;
    // }

    //TRANSITIVA HEL
    // Tupla faltaTransitiva[n];
    // int faltaTransitivaContagem = 0;
    // for (int i=name; i<n; i++){
    //     for (int j=name; j<n; j++){
    //         for (int z=name; z<n; z++){
    //             if ((Matriz[i][j] == 1) && (Matriz[j][z] == 1)){
    //                 if ((Matriz[i][z]) == 1){
    //                     transitiva = 'V';
    //                 } else {
    //                 transitiva = 'F';
    //                 faltaTransitiva[faltaTransitivaContagem].x = j;
    //                 faltaTransitiva[faltaTransitivaContagem].y = z;
    //                 faltaTransitivaContagem++;
    //                 }
    //             }
    //         }
    //     }
    // }

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

    //ASSIMÉTRICA
    //É assimétrica se for irreflexiva e anti-simétrica
    if ((irreflexiva == 'V') && (antisimetrica == 'V')) {
        assimetrica = 'V';
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
    saida = fopen("saida.txt", "w");
    //Printa Reflexiva
    fprintf(saida, "Reflexiva: %c", reflexiva);
    if (reflexiva == 'F'){
        fprintf(saida, "\n");
    }
    for (int i = 0; i < faltaReflexivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaReflexiva[i].x, faltaReflexiva[i].y);
    }
    //Printa Irreflexiva
    fprintf(saida, "\nIrreflexiva: %c", irreflexiva);
    if (irreflexiva == 'F'){
        fprintf(saida, "\n");
    }
    for (int i = 0; i < faltaIrreflexivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaIrreflexiva[i].x, faltaIrreflexiva[i].y);
    }
    //Printa Simétrica
    fprintf(saida, "\nSimétrica: %c", simetrica);
    if (simetrica == 'F'){
        fprintf(saida, "\n");
    }
    for (int i = 0; i < faltaSimetricaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaSimetrica[i].x, faltaSimetrica[i].y);
    }
    //Printa Anti-simétrica
    fprintf(saida, "\nAnti-simétrica: %c", antisimetrica);
    if (antisimetrica == 'F'){
        fprintf(saida, "\n");
    }
    for (int i = 0; i < faltaAntiSimetricaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaAntiSimetrica[i].x, faltaAntiSimetrica[i].y);
    }
    //Printa Assimétrica
    fprintf(saida, "\nAssimétrica: %c", assimetrica);
    //Printa Transitiva
    fprintf(saida, "\nTransitiva: %c", transitiva);
    if (transitiva == 'F'){
        fprintf(saida, "\n");
    }
    for (int i = 0; i < faltaTransitivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaTransitiva[i].x, faltaTransitiva[i].y);
    }
    // fprintf(saida, "\n");
    // for (int i = 0; i < faltaTransitivaSemDuplicidadeContagem; i++){
    //     fprintf(saida, "(%d,%d); ", faltaTransitivaSemDuplicidade[i].x, faltaTransitivaSemDuplicidade[i].y);
    // }
    //Printa Relação de equivalência
    fprintf(saida, "\nRelação de equivalência: %c", relacaoequivalencia);
    //Printa Relação de ordem parcial
    fprintf(saida, "\nRelação de ordem parcial: %c", relacaoordempacial);
    //Printa Fecho transitivo da relação
    fprintf(saida, "\nFecho transitivo da relação: ");
    for (int i = 0; i < fechoTransitivoContagem; i++){
        fprintf(saida, "(%d,%d); ", fechoTransitivo[i].x, fechoTransitivo[i].y);
    }
    for (int i = 0; i < faltaTransitivaContagem; i++){
        fprintf(saida, "(%d,%d); ", faltaTransitiva[i].x, faltaTransitiva[i].y);
    }

    fclose(file);
    fclose(saida);

    return 0;
}