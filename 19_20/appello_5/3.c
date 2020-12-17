//l'es sarebbe da fare con la parola in lettere maiuscole

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define dim 21

void setArrays(int *, int *);
int idonea(char *, char *, int *alpha, int *val, int *points);
int checkLetter(char l, char *alphabet, int *alpha);
void printArrays(int *a);
int countPoints(char *s, char *a, int *v);
int letterPoints(char l, char *a, int *v);

int main(){
    //set one array for cards and one for cards value with srand
    srand(time(NULL));
    int alpha[dim];
    int values[dim];
    int r, points = 0;
    char word[100] = "bacca";
    char alphabet[100] = "abcdefghilmnopqrstuvz";
    setArrays(alpha, values);
    //set this value only to check the result
    alpha[0] = 2;
    alpha[1] = 1;
    alpha[2] = 2;
    printArrays(alpha);

    r = idonea(word, alphabet, alpha, values, &points);
    printf ("error code: %d\npoints: %d\n", r, points);
    printArrays(alpha);
    printArrays(values);

    return 0;
}

void setArrays(int *alpha, int *val){
    int i = 0;

    for (; i<dim; i++){
        alpha[i] = rand()%5;
        val[i] = rand()%5+1;
    }
}

int idonea(char *word, char *alphabet, int *alpha, int *val, int *p){
    int i = 0, check;

    for (; i<strlen(word); i++){
        check = checkLetter(word[i], alphabet, alpha);
        if (check == 0)
            return 0;
    }
    *p = countPoints(word, alphabet, val);
    return 1;
}

int checkLetter(char l, char *alphabet, int *alpha){
    int i = 0, control = 0;

    for (; i<strlen(alphabet); i++){
        if (l == alphabet[i]){
            control = 1;
            if (alpha[i] > 0){
                alpha[i]--;
            }
            else
                return 0;
        }
    }
    if (control == 1)
        return 1;
    else
        return 0;
}

void printArrays(int *a){
    int i = 0;

    for (; i<dim; i++)
        printf ("%d ", a[i]);
    printf ("\n");
}

int countPoints(char *s, char *a, int *v){
    int i = 0, p = 0;

    for (; i<strlen(s); i++){
        p += letterPoints(s[i], a, v);
    }
    return p;
}

int letterPoints(char l, char *a, int *v){
    int i = 0;

    for (; i<dim; i++){
        if (l == a[i])
            return (v[i]);
    }
    return 0;
}






