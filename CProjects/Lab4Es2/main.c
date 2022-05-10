#include <stdio.h>
#define maxN 30

/*
 * Ruota il vettore di P posizioni verso
 * la direzione dir
 *
 * v = vettore
 * N = dimensione del vettore
 * P = numero posizioni (<N)
 * dir = direzione {-1, 1}
 */
void ruota(int v[], int N, int P, int dir);

/*
 * Stampa il vettore
 *
 * v = vettore
 * N = dimensione del vettore
 */
void stampaVettore(int v[], int N);

int main() {
	int N, P, dir, i;
	do {
		printf("Inserisci la quantita' di valori: ");
		scanf("%d", &N);
	} while(N < 0 || N > maxN);

	int v[N];

	for(i = 0; i < N; i++) {
		printf("Inserisci il valore #%d: ", i+1);
		scanf("%d", &v[i]);
	}

	while(P != 0) {
		do {
			printf("\nInserisci la quantita' di posizioni di cui traslare (0 < P < %d, 0 per terminare): ", N);
			scanf("%d", &P);
		} while(P < 0 || P > N);
		if(P != 0) {
			do {
				printf("Inserisci la direzione della traslazione (destra = 1, sinistra = -1): ", N);
				scanf("%d", &dir);
			} while(dir != 1 && dir != -1);
			ruota(v, N, P, dir);
			stampaVettore(v, N);
		} else {
			printf("Termino il programma...\n");
		}
	}
	return 0;
}

void ruota(int v[], int N, int P, int dir) {
	// init e initCond necessario per i casi di "parità"
	int newP = 0, i = 0, init = 0, initCond = 0;
	int t1, t2;

	// se verso sinistra, riporta a un caso verso destra
	if(dir == -1) {
		P = N - P;
	}

	t2 = v[init];
	for(i = 0; i < N && P != N; i++) {
		if(newP == init && initCond) {
			/**
			 *	se tornato all'indice iniziale prematuramente
			 *	aumenta init e ricomincia la rotazione
			 */
			init++;
			newP = (init+P)%N;
			initCond = 0;
			t2 = v[init];
		} else {
			newP = (newP+P)%N;
			initCond = 1;
		}
		t1 = v[newP];
		v[newP] = t2;
		t2 = t1;
	}
}

void stampaVettore(int v[], int N) {
	printf("Stato del vettore: ");
	for(int i = 0; i < N; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}
