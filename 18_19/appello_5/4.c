#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct el {
    int val;
    struct el *next;
};

void insertTail(struct el **, int);
void printList(struct el *);
void freeList(struct el **);
void delete(struct el **);

int main(){
    srand(time(NULL));

    int i = 0;
    struct el *head = NULL;
    while (i < 9){
        insertTail(&head, rand()%100+1);
        i++;
    }
    printList(head);
    printf("\n");
    delete(&head);
    printList(head);

    freeList(&head);
    return 0;
}

void delete(struct el **L){
    int c = 2;
    struct el *curr = *L;
    struct el *prev = NULL;

    if (curr == NULL){
        printf ("empty\n");
        return;
    }
    if (curr == *L){
        if (curr->next != NULL){
            *L = curr->next;
            free(curr);
            curr = *L;
        }
    }
    while (curr != NULL){
        prev = curr;
        curr = curr->next;
        c++;
        if (curr != NULL && c%2 != 0){
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
            c++;
        }
    }
}

void insertTail(struct el **L, int n){
    struct el *curr = *L;
    struct el *t = *L;
    struct el *node = (struct el *)malloc(sizeof(struct el));
    node->val = n;
    node->next = NULL;

    if (curr == NULL)
        *L = node;
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }
}

void printList(struct el *L){
    struct el *curr = L;

    if (L ==  NULL)
        printf ("NULL list\n");
    
    while (curr != NULL){
        printf ("%d ", curr->val);
        curr = curr->next;
    }
}

void freeList(struct el **L){
    struct el *curr = *L;
    struct el *prev = NULL;

    if (*L == NULL)
        return;
    
    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}