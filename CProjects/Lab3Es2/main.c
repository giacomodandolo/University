#include <stdio.h>
#include <string.h>

#define STRING_SIZE 50+1

//const char* removeSpaces(char string[]);

int checkExpression(char string[]);

int main() {
   int i, cond;
   char string[STRING_SIZE];
   FILE* fin = fopen("expr.txt", "r");
   for(i = 1; !feof(fin); i++) {
      fgets(string, STRING_SIZE, fin);
      if(!feof(fin)) {
         cond = checkExpression(string);
         switch(cond) {
            case 1:
               printf("Codice errore: %d\nNon e' stato letto correttamente un carattere dopo \'(\'.\n", cond, i);
               break;
            case 2:
               printf("Codice errore: %d\nNon e' stato letto correttamente un carattere dopo \')\'.\n", cond, i);
               break;
            case 3:
               printf("Codice errore: %d\nNon e' stato letto correttamente un carattere dopo un numero.\n", cond, i);
               break;
            case 4:
               printf("Codice errore: %d\nNon e' stato letto correttamente un carattere dopo un operando.\n", cond, i);
               break;
            case 5:
               printf("Codice errore: %d\nEra presente uno spazio all'interno di un numero.\n", cond, i);
               break;
            case 6:
               printf("Codice errore: %d\nLe parentesi non erano utilizzate in modo corretto.\n", cond, i);
               break;
            default:
               printf("La riga %d e' formattata correttamente.\n", i);
         }
         printf("\n");
      }
   }
   fclose(fin);
	return 0;
}

int checkExpression(char string[]) {
   int i, j = 0, parentesi = 0, number, operandFirst, operandSecond;
   char stringR[STRING_SIZE];
   for(i = 0; i < strlen(string); i++) {
      if(string[i] != ' ') {
         stringR[j] = string[i];
         j++;
      } else if((string[i-1] >= '0' && string[i-1] <= '9') && (string[i+1] >= '0' && string[i+1] <= '9')) {
         stringR[j] = string[i];
         j++;
      }
   }
   stringR[j] = '\0';

   printf("%s",stringR);

   for(i = 0; i < strlen(stringR); i++) {
      number = (stringR[i] >= '0' && stringR[i] <= '9');
      operandFirst = strchr("+-*/%", stringR[i]);
      operandSecond = strchr("+-*/%", stringR[i+1]);
      if(stringR[i] == '(') {
         parentesi++;
         if(stringR[i+1] != '(' && number) {
            return 1;
         }
      } else if(stringR[i] == ')') {
         parentesi--;
         if(parentesi < 0 || (stringR[i+1] != ')' && operandSecond == NULL) && stringR[i+1] != '\n' && stringR[i+1] != '\0') {
            return 2;
         }
      } else if(number) {
         if(stringR[i+1] != ')' && operandSecond == NULL && stringR[i+1] != '\n' && stringR[i+1] != '\0') {
            return 3;
         }
      } else if(operandFirst != NULL) {
         if(stringR[i+1] != '(' && (stringR[i+1] < '0' && stringR[i+1] > '9')) {
            return 4;
         }
      } else if(stringR[i] == ' ' && (i > 0 && i < (strlen(stringR)-1))) {
         if((stringR[i-1] >= '0' && stringR[i-1] <= '9') && (stringR[i+1] >= '0' && stringR[i+1] <= '9')) {
            return 5;
         }
      }
   }
   if(parentesi != 0) {
      return 6;
   }
   return 0;
}
