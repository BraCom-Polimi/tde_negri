#include <stdio.h>
#include <stdlib.h>

struct el {
    int val;
    struct el *next;
};

struct start {
    struct el *head;
};

struct start *createH();
void insertTail(struct start *, int);
void printList(struct start *);
void freeList(struct start *);
void ricerca(int *, struct el *, struct el *);

int main(){
    struct start *h1 = createH();
    struct start *h2 = createH();
    int r[2];

    insertTail(h1, 5);
    insertTail(h1, 4);
    insertTail(h1, 3);
    insertTail(h1, 2);
    insertTail(h1, 1);
    insertTail(h2, 1);
    insertTail(h2, 2);
    insertTail(h2, 3);
    insertTail(h2, 4);
    insertTail(h2, 5);

    printList(h1);
    printf ("\n\n");
    printList(h2);
    ricerca(r, h1->head, h2->head);
    printf ("\n\n%d\n%d\n", r[0], r[1]);

    freeList(h1);
    freeList(h2);
    return 0;
}

struct start *createH(){
    struct start *h = (struct start *)malloc(sizeof(struct start));
    h->head = NULL;
    return h;
}

void insertTail(struct start *h, int n){
    struct el *curr = h->head;
    struct el *node = (struct el *)malloc(sizeof(struct el));
    node->val = n;
    node->next = NULL;

    if (curr == NULL){
        h->head = node;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }
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

void printList(struct start *h){
    struct el *curr = h->head;

    if (curr ==  NULL)
        printf ("NULL list\n");
    
    while (curr != NULL){
        printf ("%d ", curr->val);
        curr = curr->next;
    }
}

void freeList(struct start *h){
    struct el *curr = h->head;
    struct el *prev = NULL;

    if (curr == NULL)
        return;
    
    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
    free(h);
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
