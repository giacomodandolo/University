#include <stdio.h>
#include <string.h>

int isVowel(char a);
void countAndPrint(char str[], int n);

int main() {
   char str[32] = "forExample";
   int n = 4;
   printf("Le sottostringhe di dimensione %d con almeno 2 vocali nella stringa '%s' sono ", n, str);
   countAndPrint(str, n);
   return 0;
}

int isVowel(char a) {
   int i;
   char vowels[10] = {'a','e','i','o','u','A','E','I','O','U'};
   for(i = 0; i < 10; i++) {
      if(a == vowels[i]) {
         return 1;
      }
   }
   return 0;
}

void countAndPrint(char str[], int n) {
   int i, j, count = 0, countVowels;
   for(i = 0; i < strlen(str)-n; i++) {
      countVowels = 0;
      for(j = i; j < i+n; j++) {
         if(isVowel(str[j])) {
            countVowels++;
         }
      }
      if(countVowels >= 2) {
         count++;
      }
   }
   printf("%d.\n", count);
}
