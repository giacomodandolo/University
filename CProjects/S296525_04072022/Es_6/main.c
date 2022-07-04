#include <stdio.h>
#include <string.h>

typedef struct {
   char id[5];
   float bal;
} client;

void analyseBill(FILE *fp, int *num) {
   client clients[10];
   char id[5] = "";
   float bal = 0;
   int i, flag;
   /* modifica effettuata */
   int num2 = *num;
   fscanf(fp, "%s %f", id, &bal);
   while(!feof(fp)) {
      flag = 1;
      for(i = 0; i < num2; i++) {
         if(strcmp(clients[i].id,id) == 0) {
            clients[i].bal += bal;
            flag = 0;
         }
      }
      if(flag) {
         strcpy(clients[num2].id, id);
         clients[num2].bal = bal;
         num2++;
      }
      fscanf(fp, "%s %f", id, &bal);
   }
   /* termine modifica */
   int maxIndex = 0;
   float maxBal = clients[0].bal;
   for(i = 0; i < num2; i++) {
      printf("Customer %s: %.2f\n", clients[i].id, clients[i].bal);
      if(maxBal < clients[i].bal) {
         maxBal = clients[i].bal;
         maxIndex = i;
         printf("%d %.2f\n", maxIndex, maxBal);
      }
   }
   printf("Customer with highest debt: %s, %.2f\n", clients[maxIndex].id, maxBal);
   *num = num2;
}

void main() {
   FILE *fp = fopen("bills.txt", "r");
   int num = 0;
   analyseBill(fp, &num);
   printf("%d\n", num);
}
