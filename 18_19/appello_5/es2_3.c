#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlen 100

int MAX(char str[maxlen]){
    int v[10] = {0,0,0,0,0,0,0,0,0,0};
    int i=0;
    if(str[0]=='\0') return -1;
    while(str[i] != '\0'){
        char c = str[i];
        int num = atoi(&c);
        v[num]++;
        i++;
    }
    int max = 0;
    for(i=0;i<10;i++){
        if(v[i]>=v[max])max=i;
    }
    return max;    
}


int main(int argc, char *argv[]){
    // ES 2
    char str[10] = "100393";
    printf("Il massimo nella stringa %s e' il numero %d",str,MAX(str)); 

    // ES 3
    char nomefile[20];
    strcpy(nomefile,argv[1]);
    FILE *fp;
    fp = fopen(nomefile,"r");
    if(fp == NULL) printf("Errore nell'apertura del file!");
    else{
        int prima; char primastr[maxlen];
        fscanf(fp, "%d", &prima);
        sprintf(primastr,"%d",prima);
        int N = MAX(primastr),i;
        for(i=0;i<N;i++){
            fscanf(fp, "%d", &prima);
        }
        sprintf(primastr,"%d",prima);
        printf("\n%s",primastr);
        fclose(fp);
    }
    return 0;
}