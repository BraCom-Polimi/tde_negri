#include <stdio.h>
#include <stdlib.h>

#define maxfile 20
#define max 1000


int main(int argc, char *argv[]){
    int l1,l2,l3,l4;
    int V[max];
    l1 = atoi(argv[1]);
    l2 = atoi(argv[2]);
    l3 = atoi(argv[3]);
    l4 = atoi(argv[4]);

    if(l1>l2 || l3>l4){
        printf("I numeri forniti non sono validi");
        return 0;
    }

    char nomefile[maxfile];
    printf("Prego inserire il nome del file: ");
    scanf("%s",nomefile);
    
    FILE *fp;
    fp = fopen(nomefile,"r");

    if(fp == NULL){
        printf("Errore nell'apertura del file.");
        return 0;
    }

    int i,cont=0;
    while(!feof(fp)){
        char get = fgetc(fp);
        if(get != EOF){
            char n[2];
            n[0] = get;
            n[1] = '\0';
            int num = atoi(n);
            char numtoget[num+1];
            numtoget[num] = '\0';
            for(i=0;i<num;i++){
                numtoget[i] = fgetc(fp);
            }
            int numfin = atoi(numtoget);
            if((numfin >= l1 && numfin <= l2)||(numfin > l3 && numfin < l4 )){
                if(cont<max){
                    V[cont] = numfin;
                    cont++;
                }
                else{
                    printf("Non sono riuscito a caricare un numero valido nel vettore");
                    return -1;
                }
            }
            else{
                printf("\nnumFuori: %d",numfin);
            }
        }

    }
    return 1;
}
