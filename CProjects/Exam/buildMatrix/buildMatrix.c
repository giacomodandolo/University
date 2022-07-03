#include <stdio.h>

#define MAXR 50
#define MAXC 50

int buildMatrix(int V[], int N, int M[MAXR][MAXC], int nr, int nc);
void printMatrix(int mat[MAXR][MAXC], int nr, int nc);

int main() {
   int N = 14, V[14] = {1, 2, 17, 2, 3, 1, 8, 4, 6, 1, 7, 3, 5, 2};
   int nr = 3, nc = 5, mat[MAXR][MAXC] = {   {0,0,0,0,0},
                                             {0,0,0,0,0},
                                             {0,0,0,0,0}};
   printf("%d\n", buildMatrix(V, N, mat, nr, nc));
   printMatrix(mat, nr, nc);
   return 0;
}

int buildMatrix(int V[], int N, int M[MAXR][MAXC], int nr, int nc) {
   int i, j = 0, k = 0, value, repetitions, sum = 0;
   for (i = 0; i < N; i = i + 2) {
      sum = sum + V[i+1];
   }
   if(sum > (nr*nc)) {
      return 0;
   }

   for(i = 0; i < N; i = i + 2) {
      value = V[i];
      repetitions = V[i+1];
      while(repetitions > 0) {
         M[j][k] = value;
         k++;
         if(k >= nc) {
            j++;
            k = 0;
         }
         repetitions--;
      }
   }

   return 1;
}

void printMatrix(int mat[MAXR][MAXC], int nr, int nc) {
   int i, j;
   for(i = 0; i < nr; i++) {
      printf("{ ");
      for(j = 0; j < nc; j++) {
         printf("%d ", mat[i][j]);
      }
      printf("}\n");
   }
}
