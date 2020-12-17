#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int n;
    struct node *next;
};

void insert(struct node **head, int n);
int getPost(struct node *head, int *m);
int getPrev(struct node *head, int *m);
void insertHead(struct node **n, struct node *toAdd);
void insertTail(struct node **head, int n);
void printList(struct node *head);
void freeList(struct node **head);
void insertAfterMax(struct node **head, struct node *toAdd, int max);
void insertBeforeMax(struct node **head, struct node *toAdd, int max);

int main(){
    srand(time(NULL));

    int n, i = 0, v[7] = {13,9,100,21,33,99,-200};
    struct node *head = NULL;

    while (i < 7){
        insertTail(&head, v[i]);
        i++;
    }
    insert(&head, 10);

    printList(head);
    freeList(&head);
    return 0;
}

void insertTail(struct node **head, int n){
    struct node *curr = *head;
    struct node *toAdd = (struct node *)malloc(sizeof(struct node));
    if (toAdd == NULL){
        printf ("all err\n");
        return;
    }
    toAdd->n = n;
    toAdd->next = NULL;

    if (curr == NULL){
        *head = toAdd;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = toAdd;
    }
}

void insertHead(struct node **n, struct node *toAdd){
    toAdd->next = *n;
    *n = toAdd;
}

void insert(struct node **head, int n){
    int max1, max2, max;
    struct node *N = (struct node *)malloc(sizeof(struct node));
    if (N == NULL){
        printf ("all err\n");
        return;
    }

    N->n = n;
    N->next = NULL;

    if (*head == NULL){
        *head = N;
    }
    
    else{
        max1 = getPrev(*head, &max);
        max2 = getPost(*head, &max);
        
        if (max1 == 0 && max2 == 0){
            insertHead(head, N);
        }
        else if(max2 >= max1){
            insertAfterMax(head, N, max);
        }
        else{
            insertBeforeMax(head, N, max);
        }
    }
}

void insertBeforeMax(struct node **head, struct node *toAdd, int max){
    struct node *curr = *head;
    struct node *prev = NULL;

    if (curr->n == max){
        insertHead(head, toAdd);
        return;
    }

    while (curr != NULL && curr->n != max){
        prev = curr;
        curr = curr->next;
    }
    prev->next = toAdd;
    toAdd->next = curr;
}

void insertAfterMax(struct node **head, struct node *toAdd, int max){
    struct node *curr = *head;

    //dont control first pos because we know that it will be not placed in the first pos
    while (curr != NULL && curr->n != max){
        curr = curr->next;
    }
    if (curr->next == NULL)
        curr->next = toAdd;
    else{
        toAdd->next = curr->next;
        curr->next = toAdd;
    }
}

int getPrev(struct node *head, int *m){
    int max = 0;
    struct node *curr = head;

    while (curr != NULL){
        if (curr->n > max)
            max = curr->n;
        curr = curr->next;
    }
    *m = max;
    //now we have max
    curr = head;
    //first pos case
    if (curr->n == max){
        return 0;
    }
    while (curr != NULL && curr->next->n != max){
        curr = curr->next;
    }
    //from here we are pointing to the prev of max
    return (max-(curr->n));
}

int getPost(struct node *head, int *m){
    int max = 0;
    struct node *curr = head;

    while (curr != NULL){
        if (curr->n > max)
            max = curr->n;
        curr = curr->next;
    }
    *m = max;
    //now we have max
    curr = head;
    while (curr != NULL && curr->n != max){
        curr = curr->next;
    }
    //last pos case
    if (curr->next == NULL)
        return 0;
    //from here we are pointing to the prev of max
    return (max-(curr->next->n));
}

void printList(struct node *head){
    struct node *curr = head;

    if (head ==  NULL)
        printf ("NULL list\n");
    
    while (curr != NULL){
        printf ("%d ", curr->n);
        curr = curr->next;
    }
}

void freeList(struct node **head){
    struct node *curr = *head;
    struct node *prev = NULL;

    if (*head == NULL)
        return;
    
    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}
