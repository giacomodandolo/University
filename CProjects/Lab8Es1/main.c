#include <stdio.h>
#include <stdlib.h>
#define inputFile "mappa.txt"
#define MAXR 50

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

bool leggiMatrice(int M[MAXR][MAXR], int *nr, int *nc);

/*
 * riconosce se la cella in coordinata (r,c)
 * è un estremo superiore sinistro
 * e se lo è, ricava base e altezza
 * del rettangolo
 *
 * M = matrice
 * nr = numero righe
 * nc = numero colonne
 * r = coordinata x della cella
 * c = coordinata y della cella
 * b = base (puntatore)
 * h = altezza (puntatore)
 */
bool riconosciRegione(int M[MAXR][MAXR], int nr, int nc, int r, int c, int *b, int *h);

/*
 * ricerca i rettangoli con base massima, altezza massima
 * e area massima nella matrice
 *
 * M = matrice in cui cercare
 * nr = numero righe
 * nc = numero colonne
 * max_b = rettangolo con base maggiore
 * max_h = rettangolo con altezza maggiore
 * max_a = rettangolo con area maggiore
 */
void trovaRettangoli(int M[MAXR][MAXR], int nr, int nc, rettangolo *max_b, rettangolo *max_h, rettangolo *max_a);

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
   int M[MAXR][MAXR], nr, nc, b, h, a;

   if(!leggiMatrice(M, &nr, &nc)) {
      return 1;
   }

   max_b = (rettangolo*)calloc(1, sizeof(rettangolo));
	max_h = (rettangolo*)calloc(1, sizeof(rettangolo));
	max_a = (rettangolo*)calloc(1, sizeof(rettangolo));

   max_b->b = 0;
	max_h->h = 0;
	max_a->a = 0;

   trovaRettangoli(M, nr, nc, max_b, max_h, max_a);
   printf("Max Base: \t");
   stampaRettangolo(max_b);
   printf("Max Altezza: \t");
   stampaRettangolo(max_h);
   printf("Max Area: \t");
   stampaRettangolo(max_a);
   return 0;
}

bool leggiMatrice(int M[MAXR][MAXR], int *nr, int *nc) {
   int i, j, temp;
   bool ret = TRUE;
   FILE* file;

   if((file = fopen(inputFile, "r")) == NULL) {
		printf("Non è stato possibile aprire il file '%s'. Termino il programma.\n", inputFile);
		return FALSE;
	}
   if(!feof(file)) {
		fscanf(file, " %d ", nr);
		if(!feof(file)) {
			fscanf(file, " %d ", nc);
		} else {
			printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
			ret = FALSE;
		}
	} else {
		printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
		ret = FALSE;
	}
   if(!ret) {
      fclose(file);
      return ret;
   }

   for(i = 0; i < *nr && ret; i++) {
      for(j = 0; j < *nc; j++) {
         if(!feof(file)) {
				fscanf(file, " %d ", &temp);
				if(temp == 0 || temp == 1) {
					M[i][j] = temp;
				} else {
					printf("E' stato letto un valore non valido. Termino il programma.\n");
					ret = FALSE;
               break;
				}
			} else {
				printf("Nel file non sono presenti i valori necessari. Termino il programma.\n");
				ret = FALSE;
            break;
			}
      }
   }
   fclose(file);
   return ret;
}

bool riconosciRegione(int M[MAXR][MAXR], int nr, int nc, int r, int c, int *b, int *h) {
	// se non è un estremo sinistro, termina la funzione
	if(r > 0 && M[r-1][c] == 1) {
      return FALSE;
   }
   if(c > 0 && M[r][c-1] == 1) {
      return FALSE;
   }

   int tempR, tempC;
   bool countB = TRUE;
   *b = 0;
   *h = 0;
   if(M[r][c] == 1) {
      tempR = r;
      tempC = c;
      while(M[tempR][tempC] == 1) {
         if (countB) {
            *b = *b + 1;
         }
         tempC++;
         if(tempC >= nc || M[tempR][tempC] == 0) {
            tempR++;
            tempC = c;
            *h = *h + 1;
            countB = FALSE;
         }
         if(tempR >= nr) {
            break;
         }
      }
      return TRUE;
   }
   return FALSE;
}

void trovaRettangoli(int M[MAXR][MAXR], int nr, int nc, rettangolo *max_b, rettangolo *max_h, rettangolo *max_a) {
	int i, j, tempI, tempJ, b = 0, h = 0, a;
   rettangolo *rett = (rettangolo*)calloc(1, sizeof(rettangolo));
	bool countB;

   printf("Rettangoli trovati: \n");
	for(i = 0; i < nr; i++) {
		for(j = 0; j < nc; j++) {
			countB = TRUE;
			// se trova una regione, esegue i calcoli
         if(riconosciRegione(M, nr, nc, i, j, &b, &h)) {
            a = b * h;
            cpyRettangolo(rett, i, j, b, h, a);
            stampaRettangolo(rett);
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
   printf("\n");
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
