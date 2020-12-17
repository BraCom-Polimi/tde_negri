#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    int x;
    int y;
    struct node *next;
};

void createList(struct node **V);
int ask();
struct node *createNode(int x,int y);
void printList(struct node *);
void freeList(struct node **V);
int valida(struct node *L, int *r);
double length(struct node *L);

int main(){
    int i;
    double size;
    struct node *V = NULL;
    struct node *stance = NULL;
    //create an example list
    createList(&V);
    //lets insert values for 4 times
    for (i=0; i<4; i++){
        createList(&V);
    }
    //check the list on video
    printList(V);
    printf ("size: %.2f\n", size = length(V));
    freeList(&V);

    return 0;
}

double length(struct node *L){
    double k = 0, t;
    struct node *curr = L;
    struct node *prev = NULL;
    if (curr == NULL){
        printf ("empty list\n");
        return 0;
    }
    while (curr != NULL){
        if (prev == NULL)
            t = sqrt((curr->x*curr->x)+(curr->y*curr->y));
        else
            t = sqrt((abs(curr->x-prev->x)*abs(curr->x-prev->x))+(abs(curr->y-prev->y)*abs(curr->y-prev->y)));
        k += t;
        prev = curr;
        curr = curr->next;
    }
    return k;
}

void createList(struct node **V){
    int x, y;
    struct node *curr = *V;
    struct node *toAdd = NULL;
    if (curr == NULL){
        x = ask();
        y = ask();
        toAdd = createNode(x, y);
        *V = toAdd;
        curr = *V;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        x = ask();
        y = ask();
        toAdd = createNode(x, y);
        curr->next = toAdd;
    }
}

void createList2(struct node **V, int x, int y){
    struct node *curr = *V;
    struct node *toAdd = NULL;
    if (curr == NULL){
        toAdd = createNode(x, y);
        *V = toAdd;
        curr = *V;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        toAdd = createNode(x, y);
        curr->next = toAdd;
    }
}

int ask(){
    int n;

    printf ("insert value:\n");
    scanf ("%d", &n);
    return n;
}

struct node *createNode(int x,int y){
    struct node *N = (struct node *)malloc(sizeof(struct node));
    if (N != NULL){
        N->x = x;
        N->y = y;
        N->next = NULL;
    }
    else{
        printf ("allocation error\n");
    }
    return N;
}

void printList(struct node *V){
    struct node *curr = V;
    if (curr == NULL){
        printf ("empty list\n");
    }
    else{
        while (curr != NULL){
            printf ("<%d,%d>  ", curr->x, curr->y);
            curr = curr->next;
        }
    }
}

void freeList(struct node **V){
    struct node *curr = *V;
    struct node *prev = NULL;

    if (curr == NULL){
        printf ("empty list\n");
        return;
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