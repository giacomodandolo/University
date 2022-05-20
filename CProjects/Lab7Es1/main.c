#include <stdio.h>
#include <stdlib.h>
#define inputFile "mappa.txt"

typedef struct {
	int p_x;
	int p_y;
	int b;
	int h;
	int a;
} rettangolo;

typedef enum {FALSE, TRUE} bool;

void trovaRettangoli(int** matrix, int nr, int nc, rettangolo *max_b, rettangolo *max_h, rettangolo *max_a);
void cpyRettangolo(rettangolo *rett, int p_x, int p_y, int b, int h, int a);
void stampaRettangolo(rettangolo *rett);
void stampaMatrice(int **matrix, int nr, int nc);

int main() {
	rettangolo *max_b, *max_h, *max_a;
	int i, j, nr, nc, temp;
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
			return 2;
		}
	} else {
		printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
		return 3;
	}

	int **matrix = (int**)calloc(nr, sizeof(int*));
	for(i = 0; i < nr; i++) {
		matrix[i] = (int*)calloc(nc, sizeof(int));
		for(j = 0; j < nc; j++) {
			if(!feof(file)) {
				fscanf(file, " %d ", &temp);
				if(temp == 0 || temp == 1) {
					matrix[i][j] = temp;
				} else {
					printf("E' stato letto un valore non valido. Termino il programma.\n");
					return 4;
				}
			}
		}
	}

	fclose(file);

	trovaRettangoli(matrix, nr, nc, max_b, max_h, max_a);
	printf("Max Base: ");
	stampaRettangolo(max_b);
	printf("Max Altezza: ");
	stampaRettangolo(max_h);
	printf("Max Area: ");
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
					if(tempJ >= nc || matrix[tempI][tempJ] == 0) {
						tempI++;
						tempJ = j;
						h++;
						countB = FALSE;
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
