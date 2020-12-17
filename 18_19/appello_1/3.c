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
int verifyPassage(int x, int y, int **m, int size);
void freeMatrix(int **m, int size);

int main(){
    int i, error, r = 0;
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
    error = valida(V, &r);
    printf ("\nerror code: %d\nerror value: %d\n", error, r);
    printList(V);
    freeList(&V);

    return 0;
}

int valida(struct node *L, int *r){
    int **matrix;
    int c = 0, distance = 0, i = 0, pos = 1;
    struct node *curr = L;
    struct node *prev = NULL;
    if(curr == NULL){
        printf ("empty list\n");
        *r = 1;
        return 0;
    }
    while (curr != NULL){
        c++;
        curr = curr->next;
    }
    if (c < 2){
        *r = 1;
        return 0;
    }
    curr = L;
    //we are sure that this is correct because of the two statements before
    prev = curr;
    curr = curr->next;
    //scan to view if all nodes are with distance > 0
    while (curr != NULL){
        if (prev->x == curr->x && prev->y == curr->y)
            distance = 1;
        prev = curr;
        curr = curr->next;
    }
    //now scan to view if the segment passes two times to the same spot
    //we can either create a second list to store the read values or create an temp array to store those values
    //if we use the array (easier) we must first count the list lenght
    //array approach:
    curr = L;
    c = 0;
    while (curr != NULL){
        c++;
        curr = curr->next;
    }
    matrix = (int **)malloc(c*sizeof(int *));
    for (; i<c; i++){
        matrix[i] = (int *)malloc(2*sizeof(int));
        matrix[i][0] = 0;
        matrix[i][1] = 0;
    }
    i = 0;
    curr = L;
    while (curr != NULL){
        matrix[i][0] = curr->x;
        matrix[i][1] = curr->y;
        
        //pos > 2 because we wanna al least 3 element to scan not sequential positions
        if (pos > 2){
            if(verifyPassage(curr->x, curr->y, matrix, i-1) == 1 && distance == 1){
                *r = 4;
                freeMatrix(matrix, c);
                return 0;
            }
            else if (verifyPassage(curr->x, curr->y, matrix, i-1) == 1 && distance == 0){
                *r = 3;
                freeMatrix(matrix, c);
                return 0;
            }
        }
        pos++;
        i++;
        curr = curr->next;
    }
    //if we are here is because error of point C has not occured
    if (distance == 1){
        *r = 2;
        freeMatrix(matrix, c);
        return 0;
    }
    else{
        freeMatrix(matrix, c);
        return 1;
    }
}

void freeMatrix(int **m, int size){
    int i = 0;
    for (; i<size; i++)
        free(m[i]);
    free(m);
}

int verifyPassage(int x, int y, int **m, int size){
    int i = 0;

    for (; i<size; i++){
        if (x == m[i][0] && y == m[i][1])
            return 1;
    }
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








