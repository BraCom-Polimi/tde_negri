#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxA 10
#define maxB 5

float A[maxA];
float B[maxB];
int lastA = -1;
int lastB = -1;

void riempiA(float *);
void riempiB(float *);
int riempi(float *, float *);

//suppore che A abbia almeno e elementi e he abbia n. el sempre pari - da non controllare
int main(){
    int i=0;

    srand(time(NULL));
    riempiA(A);
    riempiB(B);
 
    i = riempi(A, B);

    for (int i=0; i<=lastA; i++){
        printf ("%.0f ", A[i]);
    }
    printf ("\n\n");
    printf ("return: %d\n", i);
    return 0;
}

void riempiA(float *A){
    int i=0;

    for (; i<maxA; i++){
        if (i<6)
            A[i] = rand()%10+1;
        else
            A[i] = 0;
        printf ("%.0f ", A[i]);
    }
    printf ("\n");
    //posizione dell'ultimo elemento
    lastA = 5;
}
 
void riempiB(float *B){
    int i=0;

    for (; i<maxB; i++){
        if (i<3)
            B[i] = rand()%10+1;
        else
            B[i] = 0;
        printf ("%.0f ", B[i]);
    }
    printf ("\n");
    //posizione dell'ultimo elemento
    lastB = 2;
}

int riempi(float *A, float *B){
    //k è la quantità da inserire
    int k = lastB+1;
    int l = 0, i=0;
    int newLastA;

    //calcolo se c'è abbastanza spazio in A
    if (k > (maxA-lastA-1)){
        return 0;
    }
    else if (lastB == 0)
        return 1;
    //shiftare la seconda metà di A in avanti di tante pos quanti sono gli elementi di B da inserire
    for (i=(lastA+k); i>(lastA/2); i--){
        A[i] = A[i-k];
    }
    newLastA = lastA+k;
    for (i=(lastA/2)+1; i<=(lastA/2)+k; i++, l++){
        A[i] = B[l];
    }
    lastA = newLastA;
    return 1;
}
