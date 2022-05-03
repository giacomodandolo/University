#include <stdio.h>

int main() {
    char operation, operands[4] = {'+', '-', '*', '/'};
    float op1, op2, result;
    int right = 0;

    // inserimento da tastiera (tipo operazione)
    printf("Inserisci il tipo di operazione (+, -, *, /): ");
    do {
        operation = getchar();
        for (int i = 0; i < sizeof(operands); i++) {
            if (operation == operands[i]) {
                right = 1;
            }
        }
    } while (right != 1);

    // inserimento da tastiera (valori)
    printf("\nInserisci i valori: ");
    if (scanf("%f %f", &op1, &op2) != 2) {
        printf("Formato inserito non valido. Termino il programma.");
        return 1;
    }

    // esecuzione dell'operazione
    switch(operation) {
        case '+':
            result = op1 + op2;
            break;
        case '-':
            result = op1 - op2;
            break;
        case '*':
            result = op1 * op2;
            break;
        case '/':
            result = op1 / op2;
            break;
        default:
            printf("Valore del tipo di operazione invalido. Termino il programma.");
            return 2;
    }

    // stampa risultato
    printf("%c %.2f", operation, result);
    return 0;
}
