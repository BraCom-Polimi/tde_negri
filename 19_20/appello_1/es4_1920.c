#include <stdio.h>
#include <stdlib.h>

struct el {
    int val;
    struct el *next;
};

struct el *createList1();
struct el *createList2();
struct el *insertTail(struct el *, int);
void printList(struct el *);
void freeList(struct el *);
void ricerca(int *, struct el *, struct el *);

int main(){
    struct el *L1 = NULL;
    struct el *L2 = NULL;
    int r[2];

    L1 = insertTail(L1, 5);
    L1 = insertTail(L1, 4);
    L1 = insertTail(L1, 3);
    L1 = insertTail(L1, 2);
    L1 = insertTail(L1, 1);
    L2 = insertTail(L2, 1);
    L2 = insertTail(L2, 2);
    L2 = insertTail(L2, 3);
    L2 = insertTail(L2, 4);
    L2 = insertTail(L2, 5);
    
    printList(L1);
    printf ("\n\n");
    printList(L2);
    ricerca(r, L1, L2);
    printf ("\n\n%d\n%d\n", r[0], r[1]);

    freeList(L1);
    freeList(L2);
    return 0;
}

struct el *insertTail(struct el *L, int n){
    struct el *curr = L;
    struct el *t = L;
    struct el *node = (struct el *)malloc(sizeof(struct el));
    node->val = n;
    node->next = NULL;

    if (curr == NULL){
        curr = node;
        //return curr that will be assigned to L
        return curr;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }

    return t;
}

/*
struct el *createList1(){
    struct el *head = (struct el *)malloc(sizeof(struct el));
    struct el *curr;
    head->val = 1;
    head->next = NULL;
    curr = head;

    struct el *node1 = (struct el *)malloc(sizeof(struct el));
    node1->val = 1;
    node1->next = NULL;

    head->next = node1;

    struct el *node2 = (struct el *)malloc(sizeof(struct el));
    node2->val = 1;
    node2->next = NULL;

    node1->next = node2;

    struct el *node3 = (struct el *)malloc(sizeof(struct el));
    node3->val = 1;
    node3->next = NULL;

    node2->next = node3;

    struct el *node4 = (struct el *)malloc(sizeof(struct el));
    node4->val = 1;
    node4->next = NULL; 

    node3->next = node4;

    return curr;
}

struct el *createList2(){
    struct el *head = (struct el *)malloc(sizeof(struct el));
    struct el *curr;
    head->val = 3;
    head->next = NULL;
    curr = head;

    struct el *node1 = (struct el *)malloc(sizeof(struct el));
    node1->val = 1;
    node1->next = NULL;

    head->next = node1;

    struct el *node2 = (struct el *)malloc(sizeof(struct el));
    node2->val = 4;
    node2->next = NULL;

    node1->next = node2;

    struct el *node3 = (struct el *)malloc(sizeof(struct el));
    node3->val = 5;
    node3->next = NULL;

    node2->next = node3;
    
    struct el *node4 = (struct el *)malloc(sizeof(struct el));
    node4->val = 2;
    node4->next = NULL; 

    node3->next = node4;

    return curr;
}
*/

void printList(struct el *L){
    struct el *curr = L;

    if (L ==  NULL)
        printf ("NULL list\n");
    
    while (curr != NULL){
        printf ("%d ", curr->val);
        curr = curr->next;
    }
}

void freeList(struct el *L){
    struct el *curr = L;
    struct el *prev = NULL;

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

void ricerca(int *r, struct el *L1, struct el *L2){
    int counter1=0, counter2=0, counter=0;
    struct el *curr1 = L1;
    struct el *curr2 = L2;

    if (curr1 == NULL || curr2 == NULL){
        r[0] = 0;
        r[1] = 0;
        printf ("\nListe vuote\n");
        return;
    }

    //count the length of the two list
    while (curr1 != NULL){
        counter1++;
        curr1 = curr1->next;
    }

    while (curr2 != NULL){
        counter2++;
        curr2 = curr2->next;
    }

    if (counter1 != counter2){
        r[0] = 0;
        r[1] = 0;
        printf ("\nLe due liste non hanno la stessa lunghezza\n");
        return;
    }

    curr1 = L1;
    curr2 = L2;

    while (curr1 != NULL && curr2 != NULL){
        if (curr1->val > curr2->val)
            counter++;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    r[1] = counter;
    if (counter > (counter1/2))
        r[0] = 1;
    else
        r[0] = 0;
}
