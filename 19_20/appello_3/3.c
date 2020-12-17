#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int val;
    struct node *next;
};

void riempiL(struct node **, int n);
void stampaL(struct node *);
void freeL(struct node **);
void getP(struct node **, struct node **);
int DUP(struct node *, struct node **, int *n);

int main(){
    int n=0;
    struct node *L = NULL;
    struct node *P = NULL;

    riempiL(&L, 4);
    riempiL(&L, 6);
    riempiL(&L, 7);
    riempiL(&L, 4);
    riempiL(&L, 4);
    riempiL(&L, 7);
    riempiL(&L, 4);
    riempiL(&L, 3);
    riempiL(&L, 2);
    riempiL(&L, 9);
    riempiL(&L, 5);
    riempiL(&L, 4);

    stampaL(L);
    getP(&P, &L);

    printf ("Il valore tornato dalla funzione è: %d\nIl valore di n è: %d\n", DUP(L, &P, &n), n);
    
    freeL(&L);

    return 0;
}
//riempimento in coda
void riempiL(struct node **L, int n){
    struct node *N = (struct node *)malloc(sizeof(struct node));
    struct node *curr = *L;
    struct node *prev = NULL;

    N->val = n;
    N->next = NULL;

    if (*L == NULL)
        *L = N;
    else{
        while (curr != NULL){
            prev = curr;
            curr = curr->next;
        }
        prev->next = N;
    }
}

void stampaL(struct node *L){
    struct node *curr = L;

    if (curr == NULL){
        printf ("Lista vuota\n");
    }
    else{
        while (curr != NULL){
            printf ("%d ", curr->val);
            curr = curr->next;
        }
    }
    printf ("\n");
}

void freeL(struct node **L){
    struct node *curr = *L;
    struct node *prev = NULL;
    
    if (curr == NULL){
        printf ("Lista vuota\n");
    }
    else{
        while (curr != NULL){
            if (prev != NULL)
                free(prev);
            prev = curr;
            curr = curr->next;
        }
        free(prev);
    }
}
//supponendo di conoscere la lunghezza della lista!
void getP(struct node **P, struct node **L){
    struct node *curr = *L;
    int i=0;

    if (curr == NULL)
        printf ("Attenzione lista vuota!");
    else{
        while (i < 11){
            curr = curr->next;
            i++;
        }
        //sto passando il deundicesimo elemento della lista
        *P = curr;

        //per verifica
        printf ("\n%d\n", (*P)->val);
    }
}

int DUP(struct node *L, struct node **P, int *n){
    struct node *curr = L;
    int counter = 0;
    bool flag = false;

    while (curr != NULL){
        if (curr == *P)
            flag = true;
        curr = curr->next;
    }

    if (flag == false){
        return 0;
    }

    curr = L;
    
    while (curr != NULL && curr != *P){
        if (curr->val == (*P)->val)
            counter++;
        curr = curr->next;
    }

    *n = counter;

    return 1;
}
