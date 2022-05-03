#include <stdio.h>

int main() {
    char operation;
    float op1, op2, result;
    FILE *fOperations;
    FILE *fResults;

    // apertura file "Operations.txt" e "Results.txt"
    if((fOperations = fopen("Operations.txt", "r")) == NULL) {
        return 2;
    }
    if((fResults = fopen("Results.txt", "w")) == NULL) {
        return 3;
    }

    while(!feof(fOperations)) {
        // lettura riga formattata da "Operations.txt"
        fscanf(fOperations, "%c %f %f\n", &operation, &op1, &op2);
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
                return 4;
        }
        // inserimento riga in "Results.txt"
        fprintf(fResults, "%c %.2f \n", operation, result);
    }
    return 0;
}
