#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define dim 1000

struct node {
    int val;
    struct node *next;
};

int array[dim];

void riempiArray(int *);

int main(){
    int errore, i=0, k, counter=0;
    struct node *L = NULL;

    srand(time(NULL));
    riempiArray(array);

    for (; i < dim; i++){
        counter = 0;
        if (i == 0)
            printf ("0 - ");
        else{
            for (k=0; k<i; k++){
                if (array[k] < array[i]){
                    counter++;
                }
            }
            if (i != (dim-1))
                printf ("%d - ", counter);
            else
                printf ("%d !", counter);
        }
    }
    
    return 0;
}

void riempiArray(int *array){
    int i;

    for (i=0; i<dim; i++){
        array[i] = rand()%100+1;
    }

    for (i=0; i<dim; i++){
        printf ("%d ", array[i]);
    }
    printf ("\n");
}
