#include <stdio.h>

void maxOdd(int v[], int N);

int main() {
   int v[10] = {1, 3, 7, 1, 0, 1, 9, 3, 1, 0};
   maxOdd(v, 10);
   return 0;
}

void maxOdd(int v[], int N) {
   int i, j, maxDim = 0, dim = 0;
   for(i = 0; i < N; i++) {
      if(v[i]%2 == 1) {
         dim++;
      } else if(dim > maxDim) {
         maxDim = dim;
         dim = 0;
      }
   }
   dim = 0;
   for(i = 0; i < N; i++) {
      if(v[i]%2 == 1) {
         dim++;
      }
      if(dim == maxDim) {
         for(j = i-maxDim+1; j < i+1; j++) {
            printf("%d ", v[j]);
         }
         printf("\n");
         dim = 0;
      }
   }
}
