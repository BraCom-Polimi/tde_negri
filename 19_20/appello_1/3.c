//reading int values from a file the space will be deleted by fscanf
//if the integers in the file are written without the space from each other it will not work
//this is because if we write 1234 do we wanna say 1 & 234 or 12 & 34 or 1234 ??

#include <stdio.h>
#include <stdlib.h>

#define dim 5
#define dimS 100

int caricaMat(int [][dim], char *s);

int main(){
    int errorCode;
    int mat[dim][dim];
    char fileName[dimS] = "matrix.txt";

    //matrix to zero
    for (int i=0; i<dim; i++){
        for (int k=0; k<dim; k++){
            mat[i][k] = 0;
        }
    }

    errorCode = caricaMat(mat, fileName);

    //test the loaded matrix
    for (int i=0; i<dim; i++){
        for (int k=0; k<dim; k++){
            printf ("%2d ", mat[i][k]);
        }
        printf ("\n");
    }

    return 0;
}

int caricaMat(int M[][dim], char *s){
    int max, num, i, k, count = 0;
    FILE *f = fopen (s, "r");

    //i dont know if feof(f) is correct cause it will cicle one time more
    while (!feof(f)){ 
        fscanf (f, "%d", &num);
        printf ("%d\n", num);
        count++;
    }
    printf ("File elements: %d\n", count);
    fclose(f);

    FILE *ff;
    ff = fopen(s, "r");

    printf ("\n\n");
    if (f == NULL)
        printf ("Error file\n");
    else{
        //if the first n isnt equal to dim
        fscanf (ff, "%d", &max); 
        //this fscanf move the file pointer to the sec element of the 
        //text so when we are filling tha matrix it wll get the right value
        if (max != dim){
            printf ("max value not equal\n");
            return 0;
        }
        
        for (i=0; i<dim; i++){
            for (k=0; k<dim; k++){
                fscanf (ff, "%d", &num);
                M[k][i] = num;
            }
        }
    }
    fclose(ff);

    return 1;
}
