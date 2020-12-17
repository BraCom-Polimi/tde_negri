#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int inf = 40;
    int sup = 200;
    int vet[1000];
    int i = 0, contatore = 0, contatoreVettore = 0, n;
    char l;
    char *a;
    FILE *f = fopen("num.txt", "r");

    if (f == NULL){
        printf ("errror file\n");
        return 0;
    }

    //array to zero
    for (; i<1000; i++)
        vet[i] = 0;
    
    while (feof(f) != 1){
        l = fgetc(f);
        if (l != EOF)
            printf ("%c ", l);
        contatore++;
    }
    printf ("\ntotale caratteri: %d\n", contatore);
    fclose(f);

    //malloc of a char array, dimension: contatore
    a = (char *)malloc(contatore*sizeof(char));
    f = fopen ("num.txt", "r");
    i = 0;
    while (feof(f) != 1){
        l = fgetc(f);
        if (l == EOF)
            a[i] = '-';
        else
            a[i] = l;
        i++;
    }

    //check
    for (i=0; i<contatore; i++){
        printf ("%c", a[i]);
    }
    printf ("\n");
    //fill the vet[1000]
    for (i=0; i<contatore; i++){
        if (a[i] != ',' && a[i] != '-' && a[i] != 48){
            n = atoi(&a[i]);
            printf ("%d\n", n);
            if (n >= inf && n <= sup && contatoreVettore < 1000){
                vet[contatoreVettore] = n;
                contatoreVettore++;
            }
        }
    }
    //check
    for (i=0; i<contatoreVettore; i++){
        printf ("%d ", vet[i]);
    }
    free(a);
    fclose(f);

    return 0;
}