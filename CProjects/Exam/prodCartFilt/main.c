#include <stdio.h>
#include <stdlib.h>

void prodCartFilt(int *v1, int d1, int *v2, int d2);

int main() {
   int v1[3] = {1,2,3}, v2[4] = {3,4,5,6};
   prodCartFilt(v1, 3, v2, 4);
   return 0;
}

void prodCartFilt(int *v1, int d1, int *v2, int d2) {
   int i, j;
   for(i = 0; i < d1; i++) {
      for(j = 0; j < d2; j++) {
         if(abs(v1[i]-v2[j]) > 1) {
            printf("(%d,%d) ", v1[i], v2[j]);
         }
      }
   }
}
