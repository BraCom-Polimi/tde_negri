#include <stdio.h>
#include <stdlib.h>

struct node{
    int x;
    int y;
    struct node *next;
};

void createList(struct node **V);
void createList2(struct node **V, int x, int y);
int ask();
struct node *createNode(int x,int y);
void printList(struct node *);
void freeList(struct node **V);
int ripasso(struct node **V);
int verify(struct node **V, int size, int x, int y);

int main(){
    int i, error;
    struct node *V = NULL;
    struct node *stance = NULL;
    //create an example list
    createList(&V);
    //lets insert values for 4 times
    for (i=0; i<10; i++){
        createList(&V);
    }
    //check the list on video
    printList(V);
    error = ripasso(&V);
    printf ("\nerror code: %d\n", error);
    printList(V);
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

int ripasso(struct node **V){
    int pos = 1;
    struct node *curr = *V;
    struct node *prev = NULL;
    struct node *prevPrev = NULL;
    struct node *start = *V;
    //second list to store read values
    struct node *head = NULL;
    struct node *headCurr = NULL;
    struct node *headPrev = NULL;
    if (curr == NULL){
        printf ("empty list\n");
        return 0;
    }

    while (curr != NULL){
        createList2(&head, curr->x, curr->y);
        //> 1 cause we wanna scan until pos i-1
        if (pos > 2){
            if (verify(&head, pos-1, curr->x, curr->y) == 1){
                *V = prev;
                
                //free the temp list (head)
                headCurr = head;
                while (headCurr != NULL){
                    if (headPrev != NULL)
                        free(headPrev);
                    headPrev = headCurr;
                    headCurr = headCurr->next;
                }
                free(headPrev);
                prev = NULL;
                //free the first part of the main list
                while (start != prevPrev){
                    if (prev != NULL)
                        free(prev);
                    prev = start;
                    start = start->next;
                }
                free(start);
                free(prev);

                return 1;
            }
        }
        prevPrev = prev;
        prev = curr;
        curr = curr->next;
        pos++;
    }
    //free the temp list (head)
    headCurr = head;
    while (headCurr != NULL){
        if (headPrev != NULL)
            free(headPrev);
        headPrev = headCurr;
        headCurr = headCurr->next;
    }
    free(headPrev);

    //if we dont change the main list's head we must not free the main list's first part 
    //cause there is the free function in the main
    return 0;
}

int verify(struct node **V, int size, int x, int y){
    int pos = 1;
    struct node *curr = *V;

    if (curr == NULL){
        printf ("empty list\n");
        return 0;
    }
    while (pos < size && curr != NULL){
        if (curr->x == x && curr->y == y){
            return 1;
        }
        curr = curr->next;
        pos++;
    }
    return 0;
}




