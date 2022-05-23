#include <stdio.h>
#include <stdlib.h>
#define fSort "sort.txt"

/*
 * esegue l'algoritmo "selection sort"
 * e stampa gli scambi e le iterazioni del ciclo
 * interno, esterno e totali
 *
 * v = vettore da ordinare
 * n = dimensione del vettore
 */
void selectionSort(int *v, int n);

/*
 * esegue l'algoritmo "insertion sort"
 * e stampa gli scambi e le iterazioni del ciclo
 * interno, esterno e totali
 *
 * v = vettore da ordinare
 * n = dimensione del vettore
 */
void insertionSort(int *v, int n);

/*
 * esegue l'algoritmo "shell sort"
 * e stampa gli scambi e le iterazioni del ciclo
 * interno, esterno e totali
 *
 * v = vettore da ordinare
 * n = dimensione del vettore
 */
void shellSort(int *v, int n);

/*
 * stampa il vettore
 *
 * v = vettore da stampare
 * n = dimensione del vettore
 */
void stampaVettore(int *v, int n);

int main() {
   int *v1, *v2, *v3, n, m, i, j;
   FILE *fin;

   if((fin = fopen(fSort, "r")) == NULL) {
      printf("Non e' stato possibile aprire il file 'sort.txt'. Termino il programma.\n");
      return 1;
   }

   if(!feof(fin)) {
      fscanf(fin, " %d ", &n);
   } else {
      printf("Il file e' vuoto. Termino il programma.\n");
      return 2;
   }

   for(i = 0; i < n; i++) {
      if(!feof(fin)) {
         fscanf(fin, " %d ", &m);
         v1 = (int*)calloc(m, sizeof(int));
         v2 = (int*)calloc(m, sizeof(int));
         v3 = (int*)calloc(m, sizeof(int));
      } else {
         printf("Il file non ha elementi sufficienti. Termino il programma.\n");
         return 3;
      }

      for(j = 0; j < m; j++) {
         if(!feof(fin)) {
            fscanf(fin, " %d ", &v1[j]);
            v2[j] = v1[j];
            v3[j] = v1[j];
         } else {
            printf("Il file non ha elementi sufficienti. Termino il programma.\n");
            return 4;
         }
      }

      printf("SEQUENZA %d:\n", i+1);
      selectionSort(v1, m);
      printf("\n");
      insertionSort(v2, m);
      printf("\n");
      shellSort(v3, m);
      printf("\n\n\n");
   }

	return 0;
}

void selectionSort(int *v, int n) {
   int i, j, min, temp, scambi = 0, iterEsterno = 0, iterInterno = 0, iterTot = 0;
   for(i = 0; i < n; i++, iterEsterno++) {
      min = i;
      for(j = i + 1; j < n; j++, iterInterno++) {
         if(v[j] < v[min]) {
            min = j;
         }
      }
      if(min != i) {
         temp = v[i];
         v[i] = v[min];
         v[min] = temp;
         scambi++;
      }
   }
   iterTot = iterEsterno + iterInterno;
   printf("SELECTION SORT: \n");
   printf("Scambi effettuati: %d\n", scambi);
   printf("Iterazioni esterne: %d\n", iterEsterno);
   printf("Iterazioni interne: %d\n", iterInterno);
   printf("Iterazioni totali: %d\n", iterTot);
}

void insertionSort(int *v, int n) {
   int i, j, x, scambi = 0, iterEsterno = 0, iterInterno = 0, iterTot = 0;
   for(i = 0; i < n; i++, iterEsterno++) {
      x = v[i];
      for(j = i - 1; j >= 0 && x < v[j]; j--, iterInterno++) {
         v[j+1] = v[j];
         scambi++;
      }
      if(j+1 != i) {
         scambi++;
      }
      v[j+1] = x;
   }
   iterTot = iterEsterno + iterInterno;
   printf("INSERTION SORT: \n");
   printf("Scambi effettuati: %d\n", scambi);
   printf("Iterazioni esterne: %d\n", iterEsterno);
   printf("Iterazioni interne: %d\n", iterInterno);
   printf("Iterazioni totali: %d\n", iterTot);
}

void shellSort(int *v, int n) {
   int i, j, h = 1, x, scambi = 0, iterEsterno = 0, iterInterno = 0, iterTot = 0;
   while (h < n/3)
      h = 3*h+1;
   while(h >= 1) {
      for (i = h; i < n; i++, iterEsterno++) {
         j = i;
         x = v[i];
         for(j = i; j >= h && x < v[j-h]; j-=h, iterInterno++) {
            v[j] = v[j-h];
            scambi++;
         }
         if(j != i) {
            scambi++;
         }
         v[j] = x;
      }
      h = h/3;
   }
   iterTot = iterEsterno + iterInterno;
   printf("SHELL SORT: \n");
   printf("Scambi effettuati: %d\n", scambi);
   printf("Iterazioni esterne: %d\n", iterEsterno);
   printf("Iterazioni interne: %d\n", iterInterno);
   printf("Iterazioni totali: %d\n", iterTot);
}

void stampaVettore(int *v, int n) {
   int i;
   for(i = 0; i < n; i++) {
      printf(" %d ", v[i]);
   }
   printf("\n");
}
