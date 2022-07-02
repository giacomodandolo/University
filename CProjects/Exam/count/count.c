#include <stdio.h>
#include <string.h>

#define MAXN 49+1

int count(char A[][MAXN], int n, int m, char str[]);

int main() {
   char A[MAXN][MAXN] = {"xceca", "waecq", "dtpaz", "pcatf"}, str[MAXN] = "cat";
   printf("La parola '%s' e' presente %d volte nella matrice.\n", str, count(A, 4, 5,str));
   return 0;
}

int count(char A[][MAXN], int n, int m, char str[]) {
   int i, j, k, tempI, tempJ, bool, count = 0;
   for(i = 0; i < n; i++) {
      for(j = 0; j < m; j++) {
         bool = 1;
         if(A[i][j] == str[0] && j+1 < m) {
            tempI = i+1;
            tempJ = j+1;
            for(k = 1; k < strlen(str); k++, tempI++) {
               if(tempI >= n || A[tempI][j] != str[k]) {
                  bool = 0;
                  break;
               }
            }
            if(bool == 1) {
               count++;
            }
            bool = 1;
            for(k = 1; k < strlen(str); k++, tempJ++) {
               if(tempJ >= m || A[i][tempJ] != str[k]) {
                  bool = 0;
                  break;
               }
            }
            if(bool == 1) {
               count++;
            }
         }
      }
   }
   return count;
}
