#include <stdio.h>
#include <string.h>

typedef struct {
   int prenotazioni, C;
   float mediaC;
} giornata;

char giorni[7][10] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi", "Sabato", "Domenica"};

/* codice aggiunto */
int dayToNumber(char day[10]) {
   int i;
   for(i = 0; i < 7; i++) {
      if(strcmp(giorni[i], day) == 0) {
         return i;
      }
   }
   return -1;
}

char* numberToDay(int day) {
   return giorni[day];
}
/* fine codice aggiunto */

int printReservation(FILE *fp) {
   int maxC = 0, C = 0, i, index;
   giornata vettore[7];
   char day[10] = "";

   /* codice aggiunto */
   for(i = 0; i < 7; i++) {
      vettore[i].prenotazioni = 0;
      vettore[i].C = 0;
      vettore[i].mediaC = 0;
   }
   /* fine codice aggiunto */

   /* modifica effettuata */
   fscanf(fp, "%s %d", day, &C);
   while(!feof(fp)) {
      index = dayToNumber(day);
      vettore[index].prenotazioni++;
      vettore[index].C += C;
      fscanf(fp, "%s %d", day, &C);
   }

   for(i = 0; i < 7; i++) {
      if(vettore[i].prenotazioni != 0) {
         float prenotazioni = (float)(vettore[i].prenotazioni);
         float C2 = (float)(vettore[i].C);
         vettore[i].mediaC = C2/prenotazioni;
      }
      printf("%s: %d prenotazioni, %.2f clienti in media per tavolo.\n", numberToDay(i), vettore[i].prenotazioni, vettore[i].mediaC);
      if(vettore[i].C > maxC) {
         maxC = vettore[i].C;
      }
   }
   /* fine modifica */
   return maxC;
}

void main() {
   FILE *fin = fopen("prenotazioni.txt", "r");
   printf("%d", printReservation(fin));
   fclose(fin);
}
