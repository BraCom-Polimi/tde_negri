#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 256

int max(char *s);

int main(){
    FILE *f = fopen("file.txt", "r");
    char *s;
    int r, i = 0;
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }
    s = (char *)malloc(sizeof(char)*dim);
    if (s == NULL){
        printf ("mem err\n");
        return 0;
    }
    fgets(s, dim, f);
    if (s != NULL){
        r = max(s);
        printf ("res: %d\n", r);
        while (feof(f) != 1 && i < r){
            fgets(s, dim, f);
            printf ("%s", s);
            i++;
        }
    }
    free(s);
    fclose(f);
    
    return 0;
}

int max(char *s){
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
    printf ("\n\n");

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