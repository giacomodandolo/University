#include <stdio.h>

char codificaNumero(char c, int k);

char decodificaNumero(char c, int k);

char codificaLettera(char c0, char c1);

char decodificaLettera(char c, char c1);

int codifica(FILE *fin, FILE *fout);

int decodifica(FILE *fin, FILE *fout);

int main() {
  int scelta;
  FILE *fin, *fout;

  printf("Quale operazione vuoi eseguire sui file?\n1 - Codifica;\n2 - Decodifica.\n");
  scanf("%d", &scelta);

  switch(scelta) {
    case 1:
      fin = fopen("sorgente.txt", "r");
      fout = fopen("ricodificato.txt", "w");
      printf("Sono stati ricodificati %d caratteri.", codifica(fin, fout));
      fclose(fin);
      fclose(fout);
      break;
    case 2:
      fin = fopen("ricodificato.txt", "r");
      fout = fopen("decodificato.txt", "w");
      printf("Sono stati decodificati %d caratteri.", decodifica(fin, fout));
      fclose(fin);
      fclose(fout);
      break;
    default:
      printf("Scelta non valida. Termino il programma.\n");
  }
  return 0;
}

char codificaNumero(char c, int k) {
  char cT = c + k, cR;
  if(cT > '9') {
    cR = '0' + (cT - '9' - 1);
  } else {
    cR = cT;
  }
  return cR;
}

char codificaLettera(char c0, char c1) {
  char cD;
  // ottengo l'offset di c0 da 'a' o 'A'
  if(c0 >= 'a' && c0 <= 'z') {
    cD = c0 - 'a';
  } else if(c0 >= 'A' && c0 <= 'Z') {
    cD = c0 - 'A';
  }

  // ottengo il nuovo carattere c1
  if(c1 >= 'a' && c1 <= 'z') {
    if((c1+cD) > 'z') {
      c1 = 'a'+c1+cD-'z'-1;
    } else {
      c1 = c1 + cD;
    }
  } else {
    if((c1+cD) > 'Z') {
      c1 = 'A'+c1+cD-'Z'-1;
    } else {
      c1 = c1 + cD;
    }
  }
  return c1;
}

char decodificaNumero(char c, int k) {
  char cT = c - k, cR;
  if(cT < '0') {
    cR = '9' + (cT - '0' + 1);
  } else {
    cR = cT;
  }
  return cR;
}

char decodificaLettera(char c0, char c1) {
  char cD;
  // ottengo l'offset di c0 da 'a' o 'A'
  if(c0 >= 'a' && c0 <= 'z') {
    cD = c0 - 'a';
  } else if(c0 >= 'A' && c0 <= 'Z') {
    cD = c0 - 'A';
  }

  // ottengo il nuovo carattere c1
  if(c1 >= 'a' && c1 <= 'z') {
    if((c1-cD) < 'a') {
      c1 = 'z' + (c1-cD-'a') + 1;
    } else {
      c1 = c1 - cD;
    }
  } else {
    if((c1-cD) < 'A') {
      c1 = 'Z' + (c1-cD-'A') + 1;
    } else {
      c1 = c1 - cD;
    }
  }
  return c1;
}

int codifica(FILE *fin, FILE *fout) {
  char c0, c1, c2;
  int k = 0, cod = 0, c0Cond, c1Cond, first = 1;
  while(!feof(fin)) {
    c1 = fgetc(fin);
    if (!feof(fin)) {
      c0Cond = ((c0 >= 'a' && c0 <= 'z') || (c0 >= 'A' && c0 <= 'Z'));
      c1Cond = ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'));
      if(!first && c0Cond && c1Cond) {
        c2 = codificaLettera(c0, c1);
      } else if(c0 >= '0' && c0 <= '9'){
        c2 = codificaNumero(c0, k);
      } else {
        first = 0;
        c2 = c1;
      }
      fprintf(fout, "%c", c2);
      cod++; k++;
      c0 = c2;
    }
  }
  return cod;
}

int decodifica(FILE *fin, FILE *fout) {
  char c0, c1, c2;
  int k = 0, cod = 0, c0Cond, c1Cond, first = 1;
  while(!feof(fin)) {
    c1 = fgetc(fin);
    if (!feof(fin)) {
      c0Cond = ((c0 >= 'a' && c0 <= 'z') || (c0 >= 'A' && c0 <= 'Z'));
      c1Cond = ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'));
      if(!first && c0Cond && c1Cond) {
        c2 = decodificaLettera(c0, c1);
      } else if(c0 >= '0' && c0 <= '9'){
        c2 = decodificaNumero(c0, k);
      } else {
        first = 0;
        c2 = c1;
      }
      fprintf(fout, "%c", c2);
      cod++; k++;
      c0 = c1;
    }
  }
  return cod;
}
