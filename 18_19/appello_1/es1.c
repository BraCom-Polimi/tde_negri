#include <stdio.h>

typedef struct tnodo {
    int x;
    int y;
    struct tnodo *next;
} vertice;

vertice *spezzata1 = NULL;

int noDistance(vertice **l, vertice **primodoppio){
    vertice *temp = *l;
    vertice *back = NULL;
    while(temp != NULL){    
        if(temp->x == back->x && temp->y == back->y){ 
            primodoppio = &back;
            return 1;
        }
        back = temp;
        temp=temp->next;
    }
    return 0;
}

void cleanDist(vertice **l){
    vertice *temp = *l;
    vertice *back = NULL;
    while(temp != NULL){    
        if(temp->x == back->x && temp->y == back->y){ 
            back->next = temp->next;
            free(temp);
            temp = back;
        }
        back = temp;
        temp=temp->next;
    }
}

int ripasso(vertice **l , vertice **preint){
    vertice *temp1 = *l;
    vertice *temp2 = temp1;
    vertice *back2 = NULL;
    while(temp1 != NULL){
        while(temp2 != NULL){
            if(temp1->x = temp2->x && temp1->y == temp2->y && temp1 != temp2){
                preint = &back2;
                return 1;
            }
            back2 = temp2;
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return 0;
}

int valida(vertice *l, int *errore){
    vertice *temp = l;
    vertice *primodoppio = NULL;
    vertice *preint = NULL;
    *errore = 0; 
    int cont = 0;
    while(temp!=NULL){
        cont++;
        temp=temp->next;
    } 
    if(noDistance(&l,&primodoppio)) *errore+= 2; // Errore b)
    if (cont>=3 && ripasso(&l, &preint)) *errore+=3; // Errore c)
    if(cont<2) *errore = 1; // Errore a)
    if(*errore == 5) *errore = 4; // Ottimizzazione per il codice di errore
    if(*errore != 0) return 0;
    return 1;
}

int lunghezza(vertice *l){
    int len = 0;
    vertice *temp = l;
    while(temp->next != NULL){
        int toAdd = (temp->x - temp->next->x)^2 + (temp->y - temp->next->y)^2;
        len += toAdd;
        temp=temp->next;
    }
    return 0;
}

