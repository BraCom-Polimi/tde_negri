#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv){

    if (argc < 2)
        return 0;

    int c = 0, n, j;
    int *v;
    char l;
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
        printf ("erore\n");
    else{
        printf ("sequenza file:\n");
	fscanf (f, "%d", &n);
	c++;
	printf ("%d ", n);
        while (feof(f) != 1){
            //fscanf (f, "%d", &n);
	    l = fgetc(f);
	    if (l != EOF && l != ' '){
           	printf ("%c ", l);
            	c++;
	    }	
        }

        printf ("\nla lunghezza del file è: %d\n", c);

        fclose(f);
        f = fopen(argv[1], "r");

        if (f == NULL)
            printf ("errore\n");
        else{
            //alloco vettore di dim c
            v = (int *)malloc(c*sizeof(int));
            if (v == NULL)
                printf ("errore allocazione\n");
            j = 0;
            while (j < c){
                fscanf (f, "%d", &v[j]); 
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
