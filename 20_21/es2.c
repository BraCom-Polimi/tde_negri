#include <stdio.h>
#include <stdlib.h>

struct el {int val; struct el *next;}; 
struct el *LIS1, *LIS2;

int TRASP(struct el *l1,struct el **l2){
    if(*l2 != NULL) {
        printf("La lista 2 deve essere vuota");
        return 0;
    }
    if(l1 == NULL || l1->next == NULL){
        printf("La lista 1 non è sufficientemente lunga");
        return 0;
    }
    struct el *temp2 = NULL;

    while(l1->next != NULL){
        if(l1->val > l1->next->val){
            struct el *new = malloc(sizeof(struct el));
            if(new != NULL){
                new->val = l1->val;
                new->next = NULL;
                if(temp2 == NULL){ temp2 = new; *l2 = new;} 
                else {temp2->next = new; temp2 = temp2->next;}
            }
            else{
                printf("Memoria non sufficiente");
                return 0;
            }
        }
        l1 = l1->next;
    }

    return 1;
}


// FUNZIONI IN BASSO SOLO PER TEST (SCRITTE DA NEGRI)
struct el* inscoda(struct el *l, int val) {      struct el *nuovo, *prec;      nuovo = (struct el*) malloc(sizeof(struct el));      if (nuovo == NULL) {           printf("Out of memory!\n");           return     l;          }          nuovo -> val = val;      nuovo -> next = NULL;      if (l == NULL) {           return     nuovo;          }          prec     =     l;          while(prec -> next != NULL) {           prec = prec -> next;      }          prec -> next = nuovo;      return     l;     }
void stampalista(struct el *l)  {while(l != NULL) {printf("%d -> ", l -> val); l = l -> next;}  printf("NULL\n"); }

int main(){
    int i, ris, test[7] = {12, 7, -5, 30, 28, 65, -999};
    LIS1 = LIS2 = NULL; 
    for (i = 0; i < 7; i++) {           LIS1 = inscoda(LIS1, test[i]);      }  
    printf("Lista di partenza LIS1:\n");      stampalista(LIS1);          ris = TRASP(LIS1, &LIS2);      printf("Lista degli elementi che sono maggiori del successivo LIS2:\n");      stampalista(LIS2);
}

