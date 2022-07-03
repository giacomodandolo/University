#include <stdio.h>

#define MAXN 5

int sommaCornici(int mat[MAXN][MAXN], int N, int vet[]);

int main() {
   int mat[MAXN][MAXN] = { {1,2,3,4,5},
                           {6,7,8,9,0},
                           {1,2,3,4,5},
                           {6,7,8,9,0},
                           {1,1,1,1,1}};
   int vet[(MAXN+1)/2];
   printf("%d\n", sommaCornici(mat, MAXN, vet));
   return 0;
}

int sommaCornici(int mat[MAXN][MAXN], int N, int vet[]) {
   int i, j, limit = (MAXN+1)/2, sum, count;
   for(i = 0; i < limit; i++) {
      sum = 0;
      for(j = i; j < MAXN-i; j++) {
         if(j == i && j == MAXN-j-1) {
            sum = sum + mat[i][j];
         } else if(j == i || j == MAXN-i-1) {
            sum = sum + mat[i][j] + mat[MAXN-i-1][MAXN-j-1];
         } else {
            sum = sum + mat[i][j] + mat[j][i] + mat[MAXN-i-1][MAXN-j-1] + mat[MAXN-j-1][MAXN-i-1];
         }
      }
      printf("%d\n", sum);
   }
   return limit;
}
