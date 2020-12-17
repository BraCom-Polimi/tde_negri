/*
 *In order to set the min value on N (define) we could 
 *scan all the words present in the file and set a maxLength, but..scam
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 30

struct node{
    char *v;
    struct node *next;
};

void WORD(FILE *f, char *s, int *correct, int *read, struct node **);
bool modifyWord(char *word, char *result);
void printList(struct node *);
void freeList(struct node **);
void toList(struct node **L, char *word);

int main(){
    struct node *head = NULL;
    char *word;
    int end = 0, noWord = 0;
    FILE *f = fopen("file.txt", "r");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }
    word = (char *)malloc(sizeof(char)*dim);
    WORD(f, word, &end, &noWord, &head);
    if (noWord == 1 && end == 1){
        printf ("empty file\n");
        return 0;
    }
    else{
        printList(head);
    }


    fclose(f);
    freeList(&head);
    return 0;
}

void WORD(FILE *f, char *s, int *end, int *noWord, struct node **L){
    char letter, *word;
    int i = 0, j = 0, wordError;

    word = (char *)malloc(sizeof(char)*dim);
    if (word == NULL){
        printf ("mem err\n");
        return;
    }

    letter = fgetc(f);
    if (letter == EOF){
        *noWord = 1;
        *end = 1;
        return;
    }
    else if ((letter >= 48 && letter <= 57) || (letter >= 97 && letter <= 122) || letter == '#'){
        while (feof(f) != 1){
            //this if is useless
            if (letter != '#'){
                word[i] = letter;
                i++;
            }
            else if (strlen(word) > 0){
                word[i] = '\0';
                toList(L, word);
                free(word);
                word = (char *)malloc(sizeof(char)*dim);
                if (word == NULL){
                    printf ("mem err\n");
                    return;
                }
                i = 0;
            }
            letter = fgetc(f);  
        }
        //printf ("w: %s\n", word);
        /*
        if (modifyWord(word, s) == false){
            *end = 0;
            *noWord = 1;
        }
        else if (modifyWord(word, s) == true){
            *end = 0;
            *noWord = 0;
        }
        */
    }
}

void toList(struct node **L, char *word){
    struct node *curr = *L;
    struct node *toAdd = (struct node *)malloc(sizeof(struct node));
    if (toAdd == NULL){
        printf ("mem err\n");
        return;
    }
    toAdd->v = (char *)malloc(sizeof(char)*strlen(word));
    if (toAdd->v == NULL){
        printf ("mem err\n");
        return;
    }
    strcpy(toAdd->v, word);
    toAdd->v[strlen(word)] = '\0';
    toAdd->next = NULL;

    if (*L == NULL){
        *L = toAdd;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = toAdd;
    }
}

bool modifyWord(char *word, char *result){
    int i = 0, k = 0;
    bool flag = false;

    for (; i<strlen(word); i++){
        if (word[i] >= 97 && word[i] <= 122){
            result[k] = word[i];
            k++;
            flag = true;
        }
    }

    return flag;
}

void printList(struct node *L){
    struct node *curr = L;

    if (L ==  NULL)
        printf ("NULL list\n");
    
    while (curr != NULL){
        printf ("%s\n", curr->v);
        curr = curr->next;
    }
}

void freeList(struct node **L){
    struct node *curr = *L;
    struct node *prev = NULL;

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