#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct elemento{
    int lung;
    struct elemento *next;
    struct carattere *el;
};
struct carattere{
    char c;
    struct carattere *next;
};
struct elemento *lista;

struct elemento *carica(struct elemento *listaCa);
int ricerca(struct elemento *listaRi, char[]);

int main(){
    int scelta=3, ris;
    struct elemento *p, *pTemp, *pTemp2;
    struct carattere *a;
    char parola[10]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};//vettore "vuoto"

    p=malloc(sizeof(struct elemento));
    p=NULL;
    p=carica(p);

    while(scelta>0){
        printf("1: carica altre parole\n2: cerca parola\n3: stampa lista\n0: esci\n> ");
        scanf("%d",&scelta);
        if(scelta==1){//non richiesta e non funzionante :(
            /*pTemp=p;
            while(pTemp!=NULL){
                pTemp=pTemp->next;
            }
            pTemp=carica(pTemp);
            pTemp2=p;
            while(p!=NULL){
                p=p->next;
            }
            p->next=pTemp;
            p=pTemp2;*/
        }
        if(scelta==2){//cerca
            printf("Parola da cercare: ");
            scanf("%s",&parola);
            printf("\t\t%s\n",parola);
            ris=ricerca(p,parola);
            if(ris==0){
                printf("\t\tparola non trovata\n");
            }
        }
        if(scelta==3){//stampa
            pTemp=p;
            while(p!=NULL){
                a=p->el;
                while(a!=NULL){
                    printf("%c",a->c);
                    a=a->next;
                }
                printf("\n");
                p=p->next;
            }
            p=pTemp;
        }
    }
    return 0;
}

struct elemento *carica(struct elemento *listaCa){
    int num=-2, count, i;
    char c;
    struct elemento *t, *last;
    struct carattere *te, *laste;

    do{
        printf("N: ");
        scanf("%d",&num);
    }while(num<=0);
    fflush(stdin);

    for(i=0;i<num;i++){
        printf("stringa numero %d: ",i+1);
        count=0;
        t=malloc(sizeof(struct elemento));
        if(t==NULL){
            printf("\n\t\tERRORE");
            i=num+1;
        }
        else{
            t->next=NULL;
            t->el=NULL;
            if(listaCa==NULL){
                listaCa=t;
            }
            else{
                last->next=t;
            }
            last=t;
            c=getchar();
            while(c!='0'){
                if(c>='a'&&c<='z'){
                    count++;
                    te=malloc(sizeof(struct carattere));
                    if(te==NULL){
                        printf("\n\t\tERRORE");
                        i=num+1;
                    }
                    else{
                        te->next=NULL;
                        te->c=c;
                        if(last->el==NULL){
                            last->el=te;
                        }
                        else{
                            laste->next=te;
                        }
                        laste=te;
                    }
                    c=getchar();
                }
            }
            printf("\n\t\tparola finita\n");
            fflush(stdin);
            last->lung=count;
            printf("\t\t%d\n",last->lung);
        }
    }
    return listaCa;
}

int ricerca(struct elemento *listaRi, char V[]){
    int carattere, uguali, trovato;
    struct carattere *l, *templ;
    if(strlen(V)==0||listaRi==NULL){
        printf("\t\tparola inesistenete o lista vuota (strlen=%d)\n",strlen(V));
        return 0;
    }
    else{
        while(listaRi!=NULL){
                printf("\t\tlista!=NULL\n");
            if(listaRi->lung<strlen(V)){
                printf("\t\tprossima perche' lun e' piccola\n");
                listaRi=listaRi->next;
            }
            else{
                printf("\t\tparte il controllo\n");
                l=listaRi->el;
                carattere=0;
                trovato=0;
                printf("\t\tparola della lista lunga %d\n",listaRi->lung);
                while((trovato==0)&&(l!=NULL)){
                    if(l->c!=V[carattere]){
                        printf("\t\tprossimo carattere, questo non andava bene\n");
                        l=l->next;
                    }
                    if(l->c==V[carattere]){
                        uguali=1;
                        templ=l;
                        while((templ!=NULL)&&(V[carattere]!='\0')&&(uguali==1)){
                            if(templ->c==V[carattere]){
                                carattere++;
                                templ=templ->next;
                                printf("\t\tquesto andava bene, controllo i successivi\n");
                            }
                            else{
                                uguali=0;
                                printf("\t\tquesto non andava bene, controllo la prossima parola\n");
                                carattere=0;
                                l=l->next;
                            }
                        }
                    }
                    if((V[carattere]=='\0')&&uguali==1){
                        printf("\t\ttrovata parola\n");
                        trovato=1;
                    }
                    else{
                        if(templ==NULL){
                            return 0;
                        }
                        else{
                            l=l->next;
                            carattere=0;
                        }
                    }
                }
            }
            if(trovato==1){
                l=listaRi->el;
                while(l!=NULL){
                    printf("%c",l->c);
                    l=l->next;
                }
                printf("\n");
                return 1;
            }
            else{
                listaRi=listaRi->next;
            }
        }
    }
    return 0;
}
