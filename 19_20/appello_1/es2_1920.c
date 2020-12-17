#include <stdio.h>
#include <stdlib.h>

#define dim 5

void arrayToZero(int *, int *);
void visibile(int matrix[][dim], int *, int *);
void printResult(int *, int *);

int main(){
    int matrix[dim][dim] = {{4,5,2,3,1},{3,1,4,5,2},{1,2,5,4,3},{5,3,1,2,4},{2,4,3,1,5}};
    int row[dim];
    int col[dim];

    arrayToZero(row, col);
    visibile(matrix, row, col);
    printResult(row, col);

    return 0;
}

void arrayToZero(int row[], int col[]){
    int i=0;

    for (; i<dim; i++){
        row[i] = 0;
        col[i] = 0;
    }
}

void visibile(int matrix[][dim], int row[], int col[]){
    int i, k, max, count=1;
    //count starts from 1 because the first element is always visible

    if (dim == 0)
        return;

    //count for every row
    for (i=0; i<dim; i++){
        count = 1;
        max = matrix[i][0];
        for (k=0; k<dim; k++){
            if (matrix[i][k] > max){
                count++;
                //dont forget to upgrade max!
                max = matrix[i][k];
            }
        }
        row[i] = count;
    }

    //count for every col
    for (i=0; i<dim; i++){
        count = 1;
        max = matrix[0][i];
        for (k=0; k<dim; k++){
            if (matrix[k][i] > max){
                count++;
                max = matrix[k][i];
            }
        }
        col[i] = count;
    }
}

void printResult(int row[], int col[]){
    int i=0;

    for (i=0; i<dim; i++){
        printf ("%d ", row[i]);
    }

    printf ("\n\n");

    for (i=0; i<dim; i++){
        printf ("%d ", col[i]);
    }
    printf ("\n");
}

//{{4,5,2,3,1},{3,1,4,5,2},{1,2,5,4,3},{5,3,1,2,4},{2,4,3,1,5}};