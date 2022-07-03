#include <stdio.h>
#include <string.h>
#include <ctype.h>

int conta(char *parole[], int nparole, char *cerca);

int main(int argc, char *argv[]) {
   int result;
   result = conta(argv, argc, argv[argc-1]);
   printf("%d\n", result);
	return 0;
}

int conta(char *parole[], int nparole, char *cerca) {
   int i, j, k, count = 0, bool;
   for(i = 1; i < nparole-1; i++) {
      for(j = 0; j < strlen(parole[i]); j++) {
         if(tolower(parole[i][j]) == tolower(cerca[0])) {
            bool = 1;
            for(k = 1; k < strlen(cerca) && k < strlen(parole[i]); k++) {
               if(tolower(parole[i][j+k]) != tolower(cerca[k])) {
                  bool = 0;
                  break;
               }
            }
            if(k != strlen(cerca) && k == strlen(parole[i])) {
               bool = 0;
            }
            if(bool) {
               count++;
            }
         }
      }
   }
   return count;
}
