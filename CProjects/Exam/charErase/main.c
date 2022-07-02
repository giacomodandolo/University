#include <stdio.h>
#include <string.h>

int charErase(char str[], int pos[]);

int main() {
   char str[100] = "ThisIsAString";
   int pos[100] = {7, 4, 2, 0, 11, -1};
   printf("Sono stati modificati %d caratteri. La nuova stringa e' '%s'.", charErase(str, pos), str);
   return 0;
}

int charErase(char str[], int pos[]) {
   int i, j, count = 0, dim = strlen(str), temp;
   for(i = 0; pos[i] != -1; i++) {
      for(j = 0; pos[j+1] != -1; j++) {
         if(pos[j] > pos[j+1]) {
            temp = pos[j];
            pos[j] = pos[j+1];
            pos[j+1] = temp;
         }
      }
   }
   for(i = 0; pos[i] != -1; i++) {
      pos[i] -= count;
      if(pos[i] >= 0 && pos[i] < dim) {
         for(j = pos[i]; j < dim; j++) {
            str[j] = str[j+1];
         }
         dim--;
         count++;
      }
   }
   return count;
}
