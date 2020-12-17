#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv){
    //I dont know
    if (argc < 2)
        return 0;

    int c = 0, n, j;
    int *v;
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
        printf ("erore\n");
    else{
        printf ("sequenza file:\n");
        while (feof(f) != 1){
            fscanf (f, "%d", &n);
            printf ("%d ", n);
            c++;
        }
        //c è la lunghezza del file, faccio -- perchè la feof fa un giro di troppo
        c--;
        printf ("\nla lunghezza del file è: %d\n", c);

        fclose(f);
        f = fopen("v.txt", "r");

        if (f == NULL)
            printf ("errore\n");
        else{
            //alloco vettore di dim c
            v = (int *)malloc(c*sizeof(int));
            if (v == NULL)
                printf ("errore allocazione\n");
            j = 0;
            while (j < c){
                fscanf (f, "%d", &n);
                v[j] = n;
                j++;
            }

            //stampo vettore controllo
            printf ("vettore:\n");
            for (j=0; j<c; j++)
                printf ("%d ", v[j]);
            printf ("\n");
            }
    }
    fclose(f);
    free(v);
    return 0;
}