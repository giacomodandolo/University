#include <stdio.h>
#include <string.h>

void compressString(char *testo) {
   char repeat = testo[0], /*modifica effettuata */scount[strlen(testo)], fString[strlen(testo)];/*termine modifica*/
   int count = 1, i = 1, j = 0;

   while(repeat != '\0') {
      if(testo[i] != repeat) {
         fString[j] = repeat;
         /* modifica effettuata */
         if(count != 1) {
            sprintf(scount, "%d", count);
            fString[j+1] = *scount;
            j++;
         }
         /* termine modifica */
         repeat = testo[i];
         count = 1;
         j++;
      } else {
         count++;
      }
      i++;
   }
   fString[j] = '\0';
   printf("La stringa compressa è %s\n", fString);
}

void main() {
   char string[100] = "abbabbbaAAAAAaCCaDDDeeef\0";
   compressString(string);
}
