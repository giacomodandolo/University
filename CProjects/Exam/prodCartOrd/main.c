#include <stdio.h>

#define maxN 50

typedef struct {
   int a;
   int b;
   int sum;
} coords;

void prodCartOrd(int *v1, int d1, int *v2, int d2);
void orderCoords(coords *coordsVector, int dim);
void printCoords(coords *coordsVector, int dim);

int main() {
   int v1[3] = {2,1,3}, d1 = 3, v2[4] = {5,4,3,6}, d2 = 4;
   prodCartOrd(v1, d1, v2, d2);
   return 0;
}

void prodCartOrd(int *v1, int d1, int *v2, int d2) {
   int i, j, k = 0, dimCoords = d1*d2;
   coords coordsVector[maxN] = {};
   for(i = 0; i < d1; i++) {
      for(j = 0; j < d2; j++) {
         coordsVector[k].a = v1[i];
         coordsVector[k].b = v2[j];
         coordsVector[k].sum = v1[i]+v2[j];
         k++;
      }
   }
   orderCoords(coordsVector, dimCoords);
   printCoords(coordsVector, dimCoords);
}

void orderCoords(coords *coordsVector, int dim) {
   int i, j;
   coords temp;
   for(i = 0; i < dim; i++) {
      for(j = 0; j < dim-1; j++) {
         if(coordsVector[j].sum > coordsVector[j+1].sum) {
            temp = coordsVector[j];
            coordsVector[j] = coordsVector[j+1];
            coordsVector[j+1] = temp;
         }
      }
   }
}

void printCoords(coords *coordsVector, int dim) {
   int i, tempA = coordsVector[0].a, tempB = coordsVector[0].b;
   printf("(%d, %d) ", tempA, tempB);
   for(i = 1; i < dim; i++) {
      if(!(tempA == coordsVector[i].a && tempB == coordsVector[i].b)) {
         printf("(%d, %d) ", coordsVector[i].a, coordsVector[i].b);
         tempA = coordsVector[i].a;
         tempB = coordsVector[i].b;
      }
   }
   printf("\n");
}
