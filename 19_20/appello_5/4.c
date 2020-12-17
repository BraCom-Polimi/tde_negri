#include <stdio.h>
#include <stdlib.h>

struct node {
    int v;
    struct node *next;
};

int leggi(char *name, struct node **L);
struct node *creaNodo(int val);
void printL(struct node *);
void freeL(struct node *);

int main(){
    char name[100] = "num.txt";
    struct node *L = NULL;
    int valueR;

    valueR = leggi(name, &L);
    printL(L);
    freeL(L);
    printf ("function error code: %d\n", valueR);

    return 0;
}

int leggi(char *name, struct node **L){
    struct node *curr = *L;
    struct node *supp = NULL;
    struct node *save = NULL;
    int num;
    FILE *f;

    if (curr != NULL)
        return 0;

    f = fopen("num.txt", "r");
    while (feof(f) != 1){
        fscanf (f, "%d", &num);
        save = creaNodo(num);
        if (curr == NULL){
            *L = save;
            curr = *L;
            printf ("%d\n", (*L)->v);
        }
        //pari -> inserimento in testa
        else if (num%2 == 0){
            save->next = curr;
            *L = save;
            curr = *L;
            printf ("%d\n", (*L)->v);
        }
        //dispari -> seconda posizione
        else if (num%2 != 0){
            curr = curr->next;
            (*L)->next = save;
            save->next = curr;
            curr = *L;
            printf ("%d\n", (*L)->v);
        }
    }
    fclose(f);
    return 1;
}

struct node *creaNodo(int val){
    struct node *N = (struct node *)malloc(sizeof(struct node));

    if (N != NULL){
        N->v = val;
        N->next = NULL;
    }
    else
        printf ("errore di allocazione\n");
    
    return N;
}

void printL(struct node *L){
    struct node *curr = L;

    if (curr != NULL){
        while (curr != NULL){
            printf ("%d ", curr->v);
            curr = curr->next;
        }
    }
}

void freeL(struct node *L){
    struct node *curr = L;
    struct node *prev = NULL;

    if (curr != NULL){
        while (curr != NULL){
            if (prev != NULL)
                free(prev);
            prev = curr;
            curr = curr->next;
        }
    }
    free(prev);
}
