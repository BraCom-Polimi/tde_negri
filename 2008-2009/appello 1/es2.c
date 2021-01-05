#include<stdio.h>
#include<stdlib.h>
//1o_es2_0809
struct EL{
    int cifra;
    struct EL *successivo;
};
struct testa{
    int base;
    struct EL *primo;
} ListaCifre;

int MemorizzaInBase(struct testa *lista, int, int);
void LiberaMemoria(struct testa *lista);

int main(){

    int numero, base, risposta;
    struct testa *lista;

    printf("Inserisci la base a cui convertire:  ");
    scanf("%d",&base);
    printf("Inserisci il numero da convertire in base %d:  ",base);
    scanf("%d",&numero);
    lista=malloc(sizeof(struct testa));
    lista->primo=NULL;
    risposta=MemorizzaInBase(lista,numero,base);
    printf("\n\n\t\t%d\n\n",risposta);
    LiberaMemoria(lista);


}

int MemorizzaInBase(struct testa *l, int d, int b){
    struct EL *p;
    int r;
    printf("valore di d: %d e b: %d\n",d,b);
    if(l->primo!=NULL){
        printf("l diverso da NULL");
        return 0;
    }
    if(d==0){
            printf("d=0");
        p=malloc(sizeof(struct EL));
        if(p==NULL){
            return 0;
        }
        else{
            p->cifra=0;
            p->successivo=NULL;
            l->primo=p;
        }
    }
    else{
        while(d!=0){
            r=d%b;
            d=d/b;
            printf("resto: %d nuovo d: %d\n",r,d);
            p=malloc(sizeof(struct EL));
            if(p==NULL){
                LiberaMemoria(l);
            }
            else{
                p->cifra=r;
                p->successivo=l->primo;
                l->primo=p;
            }
        }
        return 1;
    }

}

void LiberaMemoria(struct testa *lista){
    int count=0,i;
    struct EL *v=lista->primo;
    while(v!=NULL){
        v=v->successivo;
        count++;
    }
    for(i=0;i<count;i++){
        v=lista->primo;
        lista->primo=v->successivo;
        free(v);
    }
    printf("\n\t\t\t\tmemoria liberata\n");

}
