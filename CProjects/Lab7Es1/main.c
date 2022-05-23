#include <stdio.h>
#include <stdlib.h>
#define inputFile "mappa.txt"

/*
 * struttura del rettangolo
 *
 * p_x = coordinata x
 * p_y = coordinata y
 * b = base
 * h = altezza
 * a = area
 */
typedef struct {
	int p_x;
	int p_y;
	int b;
	int h;
	int a;
} rettangolo;

/*
 * struttura del booleano
 */
typedef enum {FALSE = 0, TRUE} bool;

/*
 * ricerca i rettangoli con base massima, altezza massima
 * e area massima nella matrice
 *
 * matrix = matrice in cui cercare
 * nr = numero righe
 * nc = numero colonne
 * max_b = rettangolo con base maggiore
 * max_h = rettangolo con altezza maggiore
 * max_a = rettangolo con area maggiore
 */
void trovaRettangoli(int** matrix, int nr, int nc, rettangolo *max_b, rettangolo *max_h, rettangolo *max_a);

/*
 * copia in rettangolo i valori passati dei campi
 *
 * rett = struttura del rettangolo in cui copiare
 * p_x = coordinata x
 * p_y = coordinata y
 * b = base
 * h = altezza
 * a = area
 */
void cpyRettangolo(rettangolo *rett, int p_x, int p_y, int b, int h, int a);

/*
 * stampa i campi della struttura rettangolo
 *
 * rett = rettangolo da stampare
 */
void stampaRettangolo(rettangolo *rett);

int main() {
	rettangolo *max_b, *max_h, *max_a;
	int i, j, nr, nc, temp, ret = 0;
	bool boolRett = FALSE;
	FILE* file;

	max_b = (rettangolo*)calloc(1, sizeof(rettangolo));
	max_h = (rettangolo*)calloc(1, sizeof(rettangolo));
	max_a = (rettangolo*)calloc(1, sizeof(rettangolo));

	max_b->b = 0;
	max_h->h = 0;
	max_a->a = 0;

	if((file = fopen(inputFile, "r")) == NULL) {
		printf("Non è stato possibile aprire il file '%s'. Termino il programma.\n", inputFile);
		return 1;
	}

	if(!feof(file)) {
		fscanf(file, " %d ", &nr);
		if(!feof(file)) {
			fscanf(file, " %d ", &nc);
		} else {
			printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
			ret = 2;
		}
	} else {
		printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
		ret = 3;
	}

	if(ret != 0) {
		fclose(file);
		return ret;
	}

	int **matrix = (int**)calloc(nr, sizeof(int*));
	for(i = 0; i < nr && ret == 0; i++) {
		matrix[i] = (int*)calloc(nc, sizeof(int));
		for(j = 0; j < nc; j++) {
			if(!feof(file)) {
				fscanf(file, " %d ", &temp);
				if(temp == 0 || temp == 1) {
					matrix[i][j] = temp;
					boolRett = TRUE;
				} else {
					printf("E' stato letto un valore non valido. Termino il programma.\n");
					ret = 4;
					break;
				}
			} else {
				printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
				ret = 5;
				break;
			}
		}
	}

	fclose(file);
	/*
	 * se non è presente un rettangolo nella matrice,
	 * non esegue il codice successivo
	 */
	if(!boolRett) {
		return 6;
	}
	if(ret != 0) {
		return ret;
	}

	trovaRettangoli(matrix, nr, nc, max_b, max_h, max_a);

	printf("Max Base: \t");
	stampaRettangolo(max_b);
	printf("Max Altezza: \t");
	stampaRettangolo(max_h);
	printf("Max Area: \t");
	stampaRettangolo(max_a);
	return 0;
}

void trovaRettangoli(int **matrix, int nr, int nc, rettangolo *max_b, rettangolo *max_h, rettangolo *max_a) {
	int i, j, tempI, tempJ, b = 0, h = 0, a;
	bool countB;

	for(i = 0; i < nr; i++) {
		for(j = 0; j < nc; j++) {
			countB = TRUE;
			if(matrix[i][j] == 1) {
				tempI = i;
				tempJ = j;
				while(matrix[tempI][tempJ] == 1) {
					matrix[tempI][tempJ] = 0;
					if (countB) {
						b++;
					}
					tempJ++;
					if(tempJ >= nc || matrix[tempI][tempJ] == 0) { // se cambia riga
						tempI++;
						tempJ = j;
						h++;
						countB = FALSE; // smette di contare per la base
					}
					if(tempI >= nr) {
						break;
					}
				}
				a = b * h;
				if((max_b->b) < b) {
					cpyRettangolo(max_b, i, j, b, h, a);
				}
				if((max_h->h) < h) {
					cpyRettangolo(max_h, i, j, b, h, a);
				}
				if((max_a->a) < a) {
					cpyRettangolo(max_a, i, j, b, h, a);
				}
				b = 0;
				h = 0;
			}
		}
	}
}

void cpyRettangolo(rettangolo *rett, int p_x, int p_y, int b, int h, int a) {
	rett->p_x = p_x;
	rett->p_y = p_y;
	rett->b = b;
	rett->h = h;
	rett->a = a;
}

void stampaRettangolo(rettangolo *rett) {
	printf("Estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",
			rett->p_x,
			rett->p_y,
			rett->b,
			rett->h,
			rett->a
	);
}
