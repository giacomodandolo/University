#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define filein "input.txt"
#define fileout "output.txt"

void normalizzaTesto(FILE* fin, FILE* fout);

char controllaPunteggiatura(FILE* fin, FILE* fout);

int main() {
	FILE* fin = fopen(filein, "r");
   FILE* fout = fopen(fileout, "w");
   normalizzaTesto(fin, fout);
   fclose(fin);
   fclose(fout);
   return 0;
}

void normalizzaTesto(FILE* fin, FILE* fout) {
   char c, c1, cP;
   int cont = 0;
   while(!feof(fin)) {
      c = fgetc(fin);
      if(!feof(fin)) {
         if(c >= '0' && c <= '9') { // gestione caratteri numerici
            cP = '*';
         } else if(strchr(".,;:!?", c) != NULL) { // gestione punteggiatura
            fprintf(fout, "%c", c);
            cont++;
				if(cont == 25) {
					fprintf(fout, "| c:%d \n", cont);
					cont = 0;
				}
            if((c1 = fgetc(fin)) == ' ') { // gestione spazi multipli
               while(c1 == ' ') {
                  fprintf(fout, "%c", c1);
                  cont++;
                  if(cont == 25) {
                     fprintf(fout, "| c:%d \n", cont);
                     cont = 0;
                  }
                  c1 = fgetc(fin);
               }
            } else { // aggiunta spazio
               fprintf(fout, " ");
               cont++;
            }
            if(strchr(".!?", c) != NULL) { // se uno di questi caratteri, porta a maiuscolo
               cP = toupper(c1);
            } else {
               cP = c1;
            }
         } else {
            cP = c;
         }

			if(cP == '\n') { // se fine linea allora stampa spazi fino a 25 e termine riga
				for(int contS = cont; contS<25; contS++) {
	            fprintf(fout, " ");
	         }
	         fprintf(fout, "| c:%d\n", cont);
	         cont = 0;
	         if(strchr(".!?", c) != NULL) { // se uno di questi caratteri, stampa maiuscolo
					c = toupper(fgetc(fin));
					if (!feof(fin)) {
	            	fprintf(fout, "%c", c);
					}
					cont++;
	         }
	      } else {
	         fprintf(fout, "%c", cP);
	         cont++;
	      }
	      if(cont == 25) {
	         fprintf(fout, "| c:%d\n", cont);
	         cont = 0;
	      }
      }
   }
   return;
}
