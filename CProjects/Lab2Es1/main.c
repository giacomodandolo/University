#include <stdio.h>

int main() {
	int a = 0, b = 0, MCD;

	// inserimento due numeri interi positivi
	do {
		printf("Inserisci due numeri interi positivi:");
		scanf("%d %d", &a, &b);
	} while(a <= 0 || b <= 0);

    // scambia a, b se b > a
    if (b > a) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    // calcolo MCD
    while(b != 0) {
        MCD = b;
        b = a % b;
        a = MCD;
    }

  // stampa MCD
	printf("MCD: %d\n", MCD);
	return 0;
}
