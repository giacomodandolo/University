#include <stdio.h>
#define filein "numeri.txt"

int main() {
   FILE* fin = fopen(filein, "r");
   int a, b, r, min = 0, max = 0, scartati = 0, sum, dif, mul, div;

   fscanf(fin, " %d ", &a);
   if(!feof(fin)) {
      max = min = a;
      fscanf(fin, " %d ", &b);
      while(!feof(fin)) {
         // controllo di b per max e min
         if(max < b) {
            max = b;
         }
         if(min < b) {
            min = b;
         }
         fscanf(fin, " %d ", &r);
         // dichiarazione condizioni if
         sum = (a+b) == r;
         dif = (a-b) == r;
         mul = (a*b) == r;
         div = (b != 0 && (a/b) == r);
         if (sum || dif || mul || div) {
            // determinazione max
            if(max < r) {
               max = r;
            }
            // determinazione min
            if(min > r) {
               min = r;
            }
            // vado ai prossimi valori
            a = b;
            b = r;
         } else {
            scartati++;
         }
      }
      printf("Numero massimo: %d\n", max);
      printf("Numero minimo: %d\n", min);
      printf("Numeri scartati: %d\n", scartati);
   }
   return 0;
}
