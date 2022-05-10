#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// nomi file da aprire durante esecuzione
#define fileSor "sorgente.txt"
#define fileDiz "dizionario.txt"
#define fileRic "ricodificato.txt"
#define maxL 200

typedef struct {
   char codice[10];
   char originale[maxL+1];
} codifica;

/*
 * stampa lo stato del dizionario
 *
 * diz = dizionario da stampare
 * S = dimensione del dizionario
 */
void stampaDizionario(codifica** diz, int S);

/*
 * codifica la sorgente attraverso il dizionario
 *
 * diz = struttura dizionario
 * S = lunghezza dizionario
 * sorgente = file con testo originale
 * ricodificato = file in cui inserire il testo ricodificato
 */
void codificaSorgente(codifica** diz, int S, FILE* sorgente, FILE* ricodificato);

/*
 * sostituisce una sottostringa con una nuova sottostringa
 *
 * stringa = stringa in cui sostituire sottostringa
 * sottoStr = sottostringa da sostituire
 * nuovaStr = sottostringa con cui sostituire sottoStr
 */
void cambiaSottostringa(char stringa[], char sottoStr[], char nuovaStr[]);

int main() {
   int i, j, S;
   FILE *fDiz, *fSor, *fRic;

   if((fDiz = fopen(fileDiz, "r")) == NULL) {
      printf("Non è stato possibile aprire il dizionario.");
      return 1;
   }
   if(!feof(fDiz)) {
      fscanf(fDiz, " %d ", &S);
   } else {
      printf("Il file è vuoto.\n");
      return 2;
   }

   // allocazione memoria dizionario di strutture
   codifica** diz = (codifica**)calloc(S, sizeof(codifica*));
   for(i = 0; i < S; i++) {
      // allocazione memoria per ogni struttura
      diz[i] = (codifica*)calloc(1, sizeof(codifica));
      // ottenimento informazioni dal file e inserimento in singola struct
      fscanf(fDiz, " %s %s ", diz[i]->codice, diz[i]->originale);
   }
   fclose(fDiz);

   stampaDizionario(diz, S);

   if((fSor = fopen(fileSor, "r")) == NULL) {
      printf("Non è stato possibile aprire il dizionario.");
      return 3;
   }
   fRic = fopen(fileRic, "w");

   codificaSorgente(diz, S, fSor, fRic);

   for(i = 0; i < S; i++) {
      free(diz[i]);
   }
   free(diz);
	return 0;
}

void stampaDizionario(codifica** diz, int S) {
   for(int i = 0; i < S; i++) {
      printf("%s\t%s\n", diz[i]->codice, diz[i]->originale);
   }
}

void codificaSorgente(codifica** diz, int S, FILE* sorgente, FILE* ricodificato) {
   int i;
   char temp[maxL+1], fin;

   fscanf(sorgente, "%s", temp);
   fin = fgetc(sorgente);
   while(!feof(sorgente)) {
      for(i = 0; i < S; i++) {
         if(strstr(temp, diz[i]->originale) != NULL) {
            cambiaSottostringa(temp, diz[i]->originale, diz[i]->codice);
            break;
         }
      }
      fprintf(ricodificato, "%s%c", temp, fin);
      fscanf(sorgente, "%s", temp);
      fin = fgetc(sorgente);
   }
   fclose(sorgente);
   fclose(ricodificato);
}

void cambiaSottostringa(char stringa[], char sottoStr[], char nuovaStr[]) {
   int strLen, sottoLen, nuovaLen, i, j, k, flag, init, fin;
   strLen = strlen(stringa);
   sottoLen = strlen(sottoStr);
   nuovaLen = strlen(nuovaStr);

   for(i = 0; i < strLen; i++) {
      flag = 0;
      init = i;

      /*
       * cerca se sottostringa è in stringa
       * e trova indice inizio (j) e indice fine (i)
       */
      for(j = 0; stringa[i] == sottoStr[j]; j++, i++) {
         if(j == sottoLen-1) {
            flag = 1;
         }
         fin = i;
      }

      if(flag == 0) {
         i -= j;
      } else {
         // elimina i caratteri da sostituire
         for(j = init; j < fin; j++) {
            for(k = init; k < strLen; k++) {
               stringa[k] = stringa[k+1];
            }
            strLen--;
            i--;
         }
         // inserisce la sottostringa
         for(j = init; j < init+nuovaLen; j++) {
            for(k = strLen; k >= j; k--) {
               stringa[k+1] = stringa[k];
            }
            stringa[j] = nuovaStr[j-init];
            strLen++;
            i++;
         }
      }
   }
}
