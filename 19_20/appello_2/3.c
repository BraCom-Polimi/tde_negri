#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define dim 1000

struct node {
    int val;
    struct node *next;
};

int array[dim];

void riempiArray(int *);
int traduci(struct node **L, int *array);
void creaLista(struct node **L, int n);
int conta(struct node **L);
void printList(struct node *L);

int main(){
    int errore;
    struct node *L = NULL;

    srand(time(NULL));
    riempiArray(array);
    printf ("errore: %d\n", errore = traduci(&L, array));
    printf ("\n\n");
    printList(L);
    
    return 0;
}

void riempiArray(int *array){
    int num, i;

    for (i=0; i<dim; i++){
        num = rand()%10+1;
        if (num%2 == 0)
            array[i] = 1;
        else
            array[i] = 9;
    }

    for (i=0; i<dim; i++){
        printf ("%d ", array[i]);
    }
}

int traduci(struct node **L, int *array){
    int i, k, num, counter = 0;

    if (*L != NULL){
        printf ("Lista non vuota!\n");
        return 0;
    }

    while (i < dim && (array[i] == 1 || array[i] == 9)){
        k = i;
        if (k == 0 && array[k] == 9){
            creaLista(L, 0);
        }
        num = array[k];
        counter = 0;
        while (k < dim && (array[k] == 1 || array[k] == 9) && array[k] == num){
            counter++;
            k++;
        }
        creaLista(L, counter);
        i = k;
    }

    printf ("L'elemento piu lungo e': %d", conta(L));
    return 1;
}

void creaLista(struct node **L, int n){
    struct node *Nodo = (struct node *)malloc(sizeof(struct node));
    struct node *curr = *L;
    struct node *prev = NULL;
    

    if (Nodo != NULL){
        Nodo->val = n;
        Nodo->next = NULL;

        if (*L == NULL){
            *L = Nodo;
        }
        else{
            while (curr != NULL){
                prev = curr;
                curr = curr->next;
            }
            prev->next = Nodo;
        }
    }
    else
        printf ("Errore!\n");
}

int conta(struct node **L){
    int c = 0;
    struct node *curr = *L;

    if (curr == NULL)
        return 0;
    
    c = curr->val;
    while (curr != NULL){
        if (curr->val >= c)
            c = curr->val;
        curr = curr->next;
    }
    return c;
}

void printList(struct node *L){
    struct node *curr = L;

    if (curr == NULL)
        printf ("empty\n");
    
    while (curr != NULL){
        printf ("%d", curr->val);
        curr = curr->next;
    }
}
