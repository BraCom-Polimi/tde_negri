#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pari(int *v, int *s);

int main(){
    srand(time(NULL));
    int v[11] = {3,3,10,8,6,6,5,4,2,6,4};
    int pos, lunghezzaSottosequenza;

    //inizializzo il vettore
    /*for (int i=0; i<10; i++){
        v[i] = rand()%100+1;
        printf ("%d ", v[i]);
    }*/
    printf ("\n");

    lunghezzaSottosequenza = pari(v, &pos);
    printf ("La sequenza max è %d e inizia dalla pos %d\n", lunghezzaSottosequenza, pos);

    return 0;
}

int pari(int *v, int *s){
    int counter = 0, i;
    int max = 0;

    for (i=0; i<11; i++){
        if (v[i]%2 == 0){
            if (counter >= max)
                *s = i-counter;
            counter++;
        }
        else{
            counter = 0;
        }
        if (counter >= max)
            max = counter;
    }

    return max;
}
