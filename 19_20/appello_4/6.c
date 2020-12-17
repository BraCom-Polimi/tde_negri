#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int val;
    struct node *next;
    struct node *prev;
};

void inserimento(struct node **, int n);
void stampa(struct node *);
int ins(struct node **, int *v);
void insTesta(struct node **, int n);
void insCoda(struct node **, int n);

int main(){
    int vettore[100] = {534,6,547,5,436,54,23,4,54,7,647,46,6,346,54,73,45,43,76,455,4,6};
    int result;
    struct node *L = NULL;
    inserimento(&L, 4);
    inserimento(&L, 5);
    inserimento(&L, 2);
    inserimento(&L, 6);
    inserimento(&L, 8);

    stampa(L);
    printf ("\n\n");
    for (int i=0; i<100; i++){
        printf ("%d ", vettore[i]);
    }
    printf ("\n\n");
    result = ins(&L, vettore);
    printf ("codice errore: %d\n", result);
    stampa(L);
    return 0;
}
//facciamo inserimento in coda
void inserimento(struct node **L, int n){
    struct node *N = (struct node *)malloc(sizeof(struct node));
    struct node *curr = *L;

    if (N != NULL){
        N->val = n;
        N->prev = NULL;
        N->next = NULL;
    }
    else
        printf ("Allocazione non riuscita\n");

    if (*L == NULL){
        *L = N;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = N;
        N->prev = curr;
    }
}

void stampa(struct node *L){
    struct node *curr = L;

    if (curr != NULL){
        while (curr != NULL){
            printf ("%d ", curr->val);
            curr = curr->next;
        }
    }
    else{
        printf ("Lista vuota\n");
    }
}

int ins(struct node **L, int *v){
    int i = 0, k = 0, controllo = 0;
    struct node *curr = *L;

    if (*L == NULL)
        return 0; //se la lista è vuota restituisco codice errore 0
    //verifico se il vettore è vuoto o no
    while (i < 100){
        if (v[i] == 0) //0 è il parametro che associo al vettore vuoto
            k++;
        i++; 
    }
    if (i == k)
        return 1; //se il vettore è vuoto non modifico la lista e return 1
    i = 0;
    k = 0;
    while (i < 100 && v[i] != 0){
        controllo = 0;
        while (curr != NULL && controllo == 0){
            if (curr->val == v[i])
                controllo = 1; //elemento del vettore presente nella lista
            curr = curr->next;
        }
        if (controllo == 0 && v[i]%2 == 0)
            insTesta(L, v[i]);
        else if (controllo == 0 && v[i]%2 != 0)
            insCoda(L, v[i]);
        i++;
    }
    return 1;
}

void insTesta(struct node **L, int n){
    struct node *N = (struct node *)malloc(sizeof(struct node));
    struct node *curr = *L;

    if (N != NULL){
        N->val = n;
        N->prev = NULL;
        N->next = NULL;
    }
    else
        printf ("Allocazione non riuscita\n");
    //non verifico lista vuota perché è già verificata dal chiamante
    N->next = curr;
    curr->prev = N;
    *L = N;
}
void insCoda(struct node **L, int n){
    inserimento(L, n);
}


