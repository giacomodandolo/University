#include <stdio.h>
#define nomeFile "input.txt"

/*
 * Cerca i sottovettori di dimensione massima
 *
 * V = vettore
 * N = dimensione del vettore
 */
void sottoSequenze(int V[], int N);

/*
 * Stampa il vettore a partire dall'indice i
 * e fino all'indice N
 *
 * V = vettore
 * i = indice di inizio
 * f = indice di fine
 */
void stampaVettore(int V[], int i, int f);

int main() {
   int N;
   FILE* fin;
   if((fin = fopen(nomeFile, "r")) == NULL) {
      printf("Errore nell'aprire il file. Termino il programma.\n");
      return 1;
   }

   fscanf(fin, "%d ", &N);
   if (N > 0 && N <= 30) {
      // ottieni vettore
      int v[N], val;
      for(int i = 0; !feof(fin); i++) {
         fscanf(fin, " %d ", &val);
         v[i] = val;
      }
      // stampa sotto sequenze
      sottoSequenze(v, N);
      fclose(fin);
   } else {
      //termina programma
      printf("Il vettore non ha dimensione valida. Termino il programma. (N: %d) n", N);
      fclose(fin);
      return 2;
   }
   return 0;
}


void sottoSequenze(int V[], int N) {
   int lMax = 0, v2[N], i, l;
   // cerco la lunghezza massima e inizializzo v2 con i valori delle lunghezze
   for(i = 0, l = 0; i < N; i++) {
      if(V[i] == 0) {
         v2[i-l] = l;
         if(l > lMax) {
            lMax = l;
         }
         l = 0;
      } else {
         l++;
      }
      v2[i] = 0;
   }
   if(V[N-1] != 0) {
      v2[N-l] = l;
      if(l > lMax) {
         lMax = l;
      }
   }

   // stampo i sottovettori adatti
   printf("I sottovettori di dimensione %d sono: \n", lMax);
   for(int i = 0; i < N; i++) {
      if(v2[i] == lMax) {
         stampaVettore(V, i, lMax);
      }
   }
   return;
}

void stampaVettore(int V[], int i, int f) {
   printf("[ ");
   for(int j = 0; j < f; j++) {
      printf("%d ", V[i+j]);
   }
   printf("]\n");
}
