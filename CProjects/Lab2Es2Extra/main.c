#include <stdio.h>

int main() {
    unsigned int n, x0 = 1, x1 = 2, tmp;

    do {
        printf("Inserisci la quantita di numeri della serie di Fibonacci da mostrare:");
        scanf("%d", &n);
    } while(n <= 0);

    for(int i = 0; i < n; i++) {
        switch(i) {
            case 0:
                printf("%d", x0);
                break;
            case 1:
                printf(" %d", x1);
                break;
            default:
                tmp = x1;
                x1 = x0 * x1;
                x0 = tmp;
                printf(" %d", x1);
        }
    }
    printf("\n");
    return 0;
}
