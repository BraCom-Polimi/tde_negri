#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int val;
    struct node *next;
};

struct node *createE(int val);
void printL(struct node *L);
void insertH(struct node **L, struct node *I);
void insertT(struct node **L, struct node *I);
void freeList(struct node *L);
void listadis(struct node **old, struct node **new);

int main(){
    srand(time(NULL));
    struct node *old = NULL;
    struct node *new = NULL;
    struct node *T = NULL;
    int i = 0, n;

     while (i < 20){
        n = rand()%10;
        T = createE(n);
        insertH(&old, T);
        i++;
    }
    printL(old);

    listadis(&old, &new);
    printf ("\n");
    printL(new);

    freeList(old);
    freeList(new);

    return 0;
}

void listadis(struct node **old, struct node **new){
    int pos = 0, OLD_ELEMENTS = 0;
    struct node *CURR_OLD = *old;
    struct node *T = NULL;
    if (CURR_OLD == NULL){
        return;
    }
    while (CURR_OLD != NULL){
        OLD_ELEMENTS++;
        CURR_OLD = CURR_OLD->next;
    }

    pos = 0;
    CURR_OLD = *old;

    while (pos < OLD_ELEMENTS){
        if (pos > 0 && pos%2 != 0){
            T = createE(CURR_OLD->val);
            insertT(new, T);
        }
        CURR_OLD = CURR_OLD->next;
        pos++;
    }

}

void insertH(struct node **L, struct node *I){
    struct node *curr = *L;

    if (*L == NULL){
        *L = I;
    }
    else{
        I->next = curr;
        *L = I;
    }
}

void insertT(struct node **L, struct node *I){
    struct node *curr = *L;
    struct node *t = *L;

    if (curr == NULL)
        *L = I;
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = I;
    }
}

void freeList(struct node *L){
    struct node *curr = L;
    struct node *prev = NULL;

    if (L == NULL)
        return;
    
    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}

struct node *createE(int val){
    struct node *N = (struct node*)malloc(sizeof(struct node));
    if (N != NULL){
        N->val = val;
        N->next = NULL;
    }
    return N;
}

void printL(struct node *L){
    struct node *curr = L;
    if (curr != NULL){
        while (curr != NULL){
            printf ("%d ", curr->val);
            curr = curr->next;
        }
    }
}