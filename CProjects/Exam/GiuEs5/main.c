#include <stdio.h>
#include <string.h>
#include <ctype.h>

int textStats(char *filename) {
   char s[20+1], vowels[10+1] = "aeiouAEIOU" /* per controllare le vocali con un for*/;
   int len, m_cont = 0, i, j, bool /* prende valori 0 e 1 per controllare le parole maiuscole */, m[20];
   float vocali = 0, percentuale, cont = 0;
   FILE *fp;

   if ((fp = fopen(filename, "r")) == NULL) {
      printf("Error opening file");
      return -1;
   }

   for(i = 0; i < 20; i++) {
      m[i] = 0;
   }

   while(!feof(fp)) {
      bool = 0;
      fscanf(fp, "%s", s);
      len = strlen(s);
      m[len-1]++;

      for(i = 0; i < len; i++) {
         if (!bool && !isupper(s[i])) {
           bool = 1;
         }
         for(j = 0; j < strlen(vowels); j++) { //equivalente dell'if con tutte le vocali
            if(s[i] == vowels[j]) {
               vocali++;
               break;
            }
         }
      }
      if(!bool) {
         m_cont++;
      }
      cont++;
   }

   for (int i = 0; i < 20; i++) {
      if (m[i] != 0)
         printf("%d string/s with length %d\n", m[i], (i+1));
   }
   percentuale = (m_cont * 100) / cont;
   printf("%.2f percent with all capital letters\n", percentuale);
   vocali = vocali / cont;
   printf("Average number of vowels: %.2f\n", vocali);
   fclose(fp);
   return cont;
}

void main() {
   printf("%d\n", textStats("prova.txt"));
}
