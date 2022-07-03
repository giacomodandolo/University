#include <stdio.h>

#define MAXN 4
#define MAXM 3

void displRanking(int C[MAXN][MAXM], int n, int m);

int main() {
   int mat[MAXN][MAXM] = { {3,1,0},
                           {0,1,1},
                           {1,1,1},
                           {1,1,3}};
   printf("La squadra capolista in ognuna delle 3 giornate e': ");
   displRanking(mat, MAXN, MAXM);
}

void displRanking(int C[MAXN][MAXM], int n, int m) {
   int i, j, max, maxIndex;
   for(j = 0; j < m; j++) {
      maxIndex = 0;
      max = C[0][j];
      for(i = 0; i < n; i++) {
         if(C[i][j] > max) {
            max = C[i][j];
            maxIndex = i;
         }
      }
      printf("%d ", maxIndex);
   }
   printf("\n");
}
