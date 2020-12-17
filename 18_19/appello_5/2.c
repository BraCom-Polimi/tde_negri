#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(char s[]);

int main(){
    char s[100] = "5,7,4,3,4,65,65,65,65,65,7,45,3,65,65,52,5,6,53,62,523,53,46,3,2,2,2,2,2,65,687,68";
    int r = max(s);
    printf ("ris: %d\n", r);
    return 0;
}

int max(char s[]){
    int max, i = 0, n, *v, k = 0, counter = 0, *v2, maxF, maxFPOs;
    while (i < strlen(s)){
        n = atoi(&s[i]);
        counter++;
        if (n > max)
            max = n;
        while (i < strlen(s) && s[i] != ',')
            i++;
        i++;
    }
    //case of empty s
    if (counter == 0)
        return 0;

    v = (int *)malloc(sizeof(int)*counter);
    if (v == NULL){
        printf ("mem er\n");
        return 0;
    }
    i = 0;
    while (i < strlen(s)){
        v[k] = atoi(&s[i]);
        k++;
        while (i < strlen(s) && s[i] != ',')
            i++;
        i++;
    }
    //test
    printf ("%s\n", s);
    for (int k=0; k<counter; k++){
        printf ("%d ", v[k]);
    }

    v2 = (int *)malloc(sizeof(int)*(max*1));
    if (v2 == NULL){
        printf ("mem er\n");
        return 0;
    }
    for (i=0; i<counter; i++){
        v2[v[i]]++;
    }
    maxF = v2[0];
    maxFPOs = 0;
    //the case of two elements with the same frequence is deleted by the trick below
    for (i=0; i<=max; i++){
        if (v2[i] >= maxF){
            maxF = v2[i];
            maxFPOs = i;
        }
    }
    free(v);
    free(v2);
    return maxFPOs;
}