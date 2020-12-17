#include <stdio.h>
#include <stdlib.h>

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
int nodiStance(struct node **V);

int main(){
    int i, error;
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
    printf ("error code: %d\n", (error = nodiStance(&V)));
    printList(V);
    //free list
    freeList(&V);

    return 0;
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

int nodiStance(struct node **V){
    //assume that the list has at least 2 nodes
    struct node *head = *V;
    struct node *headPrev = NULL;
    struct node *curr = (*V)->next; //because we wanna scan from the second node
    struct node *prev = *V;
    int flag = 0;

    while (curr != NULL && flag == 0){
        if (curr->x == prev->x && curr->y == prev->y){
            flag = 1;
            while (head != prev){
                if (headPrev != NULL)
                    free(headPrev);
                headPrev = head;
                head = head->next;
            }
            free(headPrev);
            *V = curr;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}



