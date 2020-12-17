#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 256

void normalize(char *m, char *r);

int main(){
    FILE *f = fopen("polygon.txt", "r");
    int counter = 0, i = 0;
    char s[dim], **m, **r;
    
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }

    fgets(s, dim, f);
    counter++;
    //printf ("%s", s);
    while (feof(f) != 1){
        fgets(s, dim, f);
        //printf ("%s", s);
        counter++;
    }
    fclose(f);

    printf ("matrix rows: %d\n", counter);

    f = fopen("polygon.txt", "r");
    m = (char **)malloc(sizeof(char *)*counter);
    r = (char **)malloc(sizeof(char *)*counter);
    for (; i<counter; i++){
        m[i] = (char *)malloc(sizeof(char)*dim);
        r[i] = (char *)malloc(sizeof(char)*dim);

        if (m[i] == NULL){
            printf ("mem err\n");
            return 0;
        }

        fgets(m[i], dim, f);
        printf("%s", m[i]);
    }
    fclose(f);

    printf ("\n\n");
    
    f = fopen("normalized_polygon.txt", "w");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }

    for (i=0; i<counter; i++){
        normalize(m[i], r[i]);
        printf ("%s", r[i]);
        fputs(r[i], f);
    }
    fclose(f);

    return 0;
}

void normalize(char *m, char *r){
    int i = 0, rI;

    //pointer to the last N of POLYGON
    while (i < strlen(m) && m[i] != 'N'){
        r[i] = m[i];
        i++;
    }
    //this is for the N
    r[i] = m[i];
    rI = (i+1);

    //pointer to the first '('
    while (i < strlen(m) && m[i] != '('){
        i++;
    }

    while (i < strlen(m)){
        if (m[i] == '(' || m[i] == ')' || m[i] == ',' || (m[i] >= 48 && m[i] <= 57) || m[i] == '.'){
            //this if is to separe '00' to '0 0' , other conditions are for constrains
            if ((m[i-1] >= 48 && m[i-1] <= 57) && (m[i] != ',' && m[i] != '(' && m[i] != ')')){ 
                r[rI] = ' ';
                rI++;
            }
            r[rI] = m[i];
            rI++;
        }
        else if (m[i] == ' '){
            if ((r[rI-1] >= 48 && r[rI-1] <= 57) && (m[i+1] != ',')){
                r[rI] = ' ';
                rI++;
            }
        }
        i++;
    }
    r[rI] = '\n';
    r[rI+1] = '\0';
}