#include <stdio.h>
#include <stdlib.h>

#define N 4
typedef unsigned int riga[N];

riga M[N] = {{4, 10, 5, 1},{0, 2, 6, 0},{7, 4, 12, 8},{0, 7, 8, 0}};
double geodist(int s1, int s2) {return abs(s2 - s1);}

int main(){
    int i,k,ddiag=0,dcol=0,drow=0;

    if(N == 1){
        printf("Caso degenere. Diagonale perde");
        return 0;
    }

    for(i=0;i<N-1;i++){
        ddiag += geodist(M[i][i],M[i+1][i+1]);
    }
    
    for(i=0;i<N;i++){
        for(k=1;k<N-1;k++){
            dcol += geodist(M[i][k],M[i][k+1]);
        }
        if(dcol < ddiag){ printf("Perde diagonale"); return 0;}
        dcol = 0;
    }

    for(i=0;i<N;i++){
        for(k=1;k<N-1;k++){
            drow += geodist(M[k][i],M[k+1][i]);
        }
        if(drow < ddiag){ printf("Perde diagonale"); return 0;}
        drow = 0;
    }

    printf("Diagonale vince");
    return 0;
}
