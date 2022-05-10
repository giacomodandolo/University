#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 20
#define MAX_NOMEFILE 20

/**
 * stampa una matrice
 *
 * matrix = matrice da stampare
 * nr = numero righe
 * nc = numero colonne
 */
void stampaMatrice(int **matrix, int nr, int nc);

/**
 * stampa tutte le sottomatrici quadrate e trova
 * quella con somma massima degli elementi
 *
 * matrix = matrice
 * nr = numero righe
 * nc = numero colonne
 * dim = dimensione sottomatrice quadrata
 */
void trovaSottomatriceMax(int **matrix, int nr, int nc, int dim);

/**
 * somma gli elementi della sottomatrice quadrata di coordinate
 *	[r -> r+dim][c -> c+dim] e la ritorna
 *
 * matrix = matrice totale
 * tempMatrix = matrice temporanea
 * r = numero righe
 * c = numero colonne
 * dim = dimensione sottomatrice quadrata
 */
int sommaSottomatrice(int **matrix, int **tempMatrix, int r, int c, int dim);

/**
 * copia la matrice quadrata m2 nella matrice quadrata m1
 *
 * m1 = matrice contenitore
 * m2 = matrice da cui copiare
 * dim = dimensioni righe e colonne
 */
void copiaMatrice(int **m1, int** m2, int dim);

int main() {
	FILE* fin;
	int i, j, nr, nc, dim, maxD,**matrix;
	char nomeFile[MAX_NOMEFILE+1];

	printf("Inserisci il nome del file: ");
	scanf("%s", nomeFile);

	if((fin = fopen(nomeFile, "r")) == NULL) {
		printf("Non è stato possibile aprire il file.");
		return 1;
	}

	// ottieni numero di righe e colonne
	if(!feof(fin)) {
		fscanf(fin, " %d ", &nr);
		if(nr < 1 || nr > MAX_DIM) {
			printf("Il numero di righe non e' un valore valido (1 <= nr <= 20).");
			return 2;
		}
		if(!feof(fin)) {
			fscanf(fin, " %d ", &nc);
			if(nc < 1 || nc > MAX_DIM) {
				printf("Il numero di colonne non e' un valore valido (1 <= nc <= 20).");
				return 4;
			}
		} else {
			printf("Errore nella lettura delle colonne.");
			return 5;
		}
	} else {
		printf("Errore nella lettura delle righe.");
		return 3;
	}

	// allocazione dinamica della matrice
	matrix = (int**)calloc(nr, sizeof(int*)); // righe
	for(i = 0; i < nr; i++) {
		matrix[i] = (int*)calloc(nc, sizeof(int)); // colonne
	}

	// lettura valori matrice
	for(i = 0; i < nr; i++) {
		for(j = 0; j < nc; j++) {
			if(!feof(fin)) {
				fscanf(fin, " %d ", &matrix[i][j]);
			} else {
				printf("Errore nella lettura dei valori della matrice.");
				return 6;
			}
		}
	}
	fclose(fin);

	printf("Matrice: \n");
	stampaMatrice(matrix, nr, nc);
	printf("\n");

	// determina la dimensione massima
	if(nr < nc) {
		maxD = nr;
	} else {
		maxD = nc;
	}

	// controllo dimensione ed effettiva esecuzione programma
	printf("Inserisci la dimensione delle sottomatrici da ricercare (1 <= dim <= %d): ", maxD);
	scanf("%d", &dim);
	while(dim >= 1 && dim <= maxD) {
		trovaSottomatriceMax(matrix, nr, nc, dim);
		printf("Inserisci la dimensione delle sottomatrici da ricercare (1 <= dim <= %d): ", maxD);
		scanf("%d", &dim);
	}

	printf("Termino il programma...\n");

	// libera memoria
	for(i=0; i < nr; i++){
		 free(matrix[i]);
	}
	free(matrix);
	return 0;
}

void stampaMatrice(int **matrix, int nr, int nc) {
	int i, j;
	for(i = 0; i < nr; i++) {
		for(j = 0; j < nc; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void trovaSottomatriceMax(int **matrix, int nr, int nc, int dim) {
	int i, j, tempSum = 0, maxSum = 0, **tempMatrix, **maxMatrix;

	// allora memoria per matrice temporanea e matrice massima
	tempMatrix = (int**)calloc(dim, sizeof(int*));
	maxMatrix = (int**)calloc(dim, sizeof(int*));
	for(i = 0; i < dim; i++) {
		tempMatrix[i] = (int*)calloc(dim, sizeof(int));
		maxMatrix[i] = (int*)calloc(dim, sizeof(int));
	}

	printf("Le sottomatrici di dimensione %d sono:\n", dim);
	for(i = 0; i < nr - (dim - 1); i++) {
		for(j = 0; j < nc - (dim - 1); j++) {
			tempSum = sommaSottomatrice(matrix, tempMatrix, i, j, dim);
			if(tempSum > maxSum) {
				maxSum = tempSum;
				copiaMatrice(maxMatrix, tempMatrix, dim);
			}
			stampaMatrice(tempMatrix, dim, dim);
			printf("\n");
		}
	}

	printf("La sottomatrice con la somma massima %d e':\n", maxSum);
	stampaMatrice(maxMatrix, dim, dim);
	printf("\n");

	// libera memoria
	for(i=0; i<dim; i++){
		 free(tempMatrix[i]);
		 free(maxMatrix[i]);
	}
	free(tempMatrix);
	free(maxMatrix);
}

int sommaSottomatrice(int **matrix, int **tempMatrix, int r, int c, int dim) {
	int i, j, sum = 0;
	for(i = r; i < r + dim; i++) {
		for(j = c; j < c + dim; j++) {
			sum += matrix[i][j];
			tempMatrix[i-r][j-c] = matrix[i][j];
		}
	}
	return sum;
}

void copiaMatrice(int **m1, int** m2, int dim) {
	int i, j;
	for(i = 0; i < dim; i++) {
		for(j = 0; j < dim; j++) {
			m1[i][j] = m2[i][j];
		}
	}
}
