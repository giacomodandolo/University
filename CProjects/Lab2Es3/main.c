#include <stdio.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main() {
	// comprimi
	FILE *fin = fopen("sorgente.txt", "r");
	FILE *fout = fopen("compresso.txt", "w");
	comprimi(fin, fout);
	fclose(fin);
	fclose(fout);

	// decomprimi
	FILE *fin2 = fopen("compresso.txt", "r");
	FILE *fout2 = fopen("decompresso.txt", "w");
	decomprimi(fin2, fout2);
	fclose(fin2);
	fclose(fout2);
	return 0;
}

int comprimi(FILE *fin, FILE *fout) {
	char c1 = fgetc(fin), c2;
	int contatore = 0;
	// controllo la fine del file
	while(!feof(fin)) {
		// prende il carattere successivo
		c2 = fgetc(fin);
		// se ritrova il carattere aumenta il contatore fino a 9
		while(c1 == c2 && contatore < 9) {
			contatore++;
			c2 = fgetc(fin);
		}
		// se la ricorrenza è di più di 2 caratteri, stampa la quantità di ricorrenze
		if(contatore > 1) {
			fprintf(fout, "%c$%d", c1, contatore);
		} else {
			for(int i = 0; i < contatore+1; i++) {
				fprintf(fout, "%c", c1);
			}
		}
		contatore = 0;
		c1 = c2;
	}
}

int decomprimi(FILE *fin, FILE *fout) {
	char c1 = fgetc(fin), c2, c3;
	// controllo la fine del file
	while(!feof(fin)) {
		// prende il carattere successivo
		c2 = fgetc(fin);
		// se il carattere è ricorrente
		if (c2 == '$') {
			c3 = (int)(fgetc(fin)-'0')+1;
			// print nel file del carattere tot volte
			for(int i = 0; i < c3; i++) {
				fprintf(fout, "%c", c1);
			}
			c1 = fgetc(fin);
		} else {	// se non è ricorrente
			fprintf(fout, "%c", c1);
			c1 = c2;
		}
	}
}
