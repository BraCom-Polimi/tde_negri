/* 
Francesco Buccoliero
14/12/2020
Esercitazione Prof.Visentini

Super Credits: Matteo, super helpful e disponibilissimo per chiarire ogni dubbio
 */

// Librerie brutte che ha implementato Matteo, non so se servano tutte in realtà :3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Numero massimo di nodi che genera automaticamente il programma
#define DIM 10
// E la lunghezza massima del path su cui salvare la lista
#define PATH_LEN 100

// Definisco il nodo
struct s_elem{
    // Due proprietà del nodo
    char codice; 
    int quantita;
    // E il puntatore all'elemento successivo
    struct s_elem *next;
};

// Serve nelle ultime due funzioni per caricare i file
typedef enum {txt,bin} t_file;

// [NON RICHIESTA]
// Funzione estetica che conta il numero di nodi
int listLength(struct s_elem *list){
    int i=0;
    if(list == NULL){
        return 0;
    }
    else {
        struct s_elem *temp = list;
        while(temp != NULL){
            i++;
            temp=temp->next;
        }
        return i;
    }
}

// Funzione che stampa la lista
void stampalista(struct s_elem *testa, char etichetta[]){
    // Stampiamo prima l'etichetta con la lunghezza della lista
    printf("\n%s (%d): ",etichetta,listLength(testa));

    // Creo un puntatore temporaneo per scorrere la lista
    struct s_elem *temp = testa;

    // Se la lista non è nulla ...
    if(temp != NULL){
        // ... e finchè non lo diventerà
        while(temp != NULL){
            // Stampo senza pietà le sue proprietà
            printf("[%c,%d]->",temp->codice,temp->quantita);
            // E vado avanti, sostituendo al puntatore "temp" il suo "next"
            temp = temp->next;
        }
        printf("NULL"); 
    }
    else{ printf("Lista vuota!");}
}

// Questa funzione è responsabile dell'allocazione di memoria
// necessaria per la creazione del nostro nodo
// la chiameremo ogni volta che ci servirà creare nuovi nodi
struct s_elem *creaelem(char codice, int quantita){

    // Questa brutta riga crea un puntatore ad un elemento di tipo "nodo"
    // gli fa spazio nella RAM, allocandogli memoria con malloc()
    struct s_elem *N = (struct s_elem *) malloc(sizeof(struct s_elem));
    // Se tutto è andato bene, questo puntatore non sarà nullo
    if(N != NULL){
        // E quindi riempiamo il nodo con le informazioni
        N->codice = codice;
        N->quantita = quantita;
        // Il puntatore al suo successivo non lo sappiamo ancora per
        // ora lo lasciamo NULL, poi la funzione inserisci(testa/coda)
        // penserà a riempirlo
        N->next = NULL;
    }
    
    return N;
}

// Questa funzione prende un puntatore alla lista, un elemento
// ed aggiunge l'elemento in testa alla lista
void inseriscitesta(struct s_elem **testa, struct s_elem *new){
    // Se non c'è niente in testa, quindi la lista è vuota...
    if(*testa == NULL){
        // Il nuovo elemento diventa la testa (e la coda)
        *testa=new;
    }
    else{
        // Altrimenti imposto il "next" del mio nuovo nodo 
        // per puntare alla vecchia testa
        new->next = *testa;
        // e il puntatore che prima puntava alla vecchia testa ora
        // punta al nostro nuovo nodo, che è diventato la nuova testa
        *testa = new;
    }
}

// Questa funzione prende un puntatore alla lista, un elemento
// ed aggiunge l'elemento in coda alla lista
void inseriscicoda(struct s_elem **lista, struct s_elem *new){
    // Se non c'è niente in testa, quindi la lista è vuota...
    if(*lista == NULL){
        // Il nuovo elemento diventa la testa (e la coda)
        *lista=new;
    }
    else{
        // Altrimenti, con l'uso di un puntatore temporaneo
        struct s_elem *temp = *lista;
        // Scorro la lista fino a trovare l'ultimo elemento
        while(temp->next != NULL){
            temp=temp->next;
        }
        // E gli modifico il valore "next" assegnandogli
        // il puntatore del mio nuovo elemento
        temp->next = new;        
    }
}

// Questa funzione cerca nella lista il primo elemento che
// ha come parametro "codice" un codice "c" passato 
struct s_elem *cercaelem(struct s_elem **lista , char c){
    // Se la lista è vuota non c'è sicuramente nulla
    if(*lista == NULL) {
        return NULL;
    }
    else {
        // Altrimenti, come prima, uso un punt. temp. per scorrere
        struct s_elem *temp = *lista;
        // Finchè non lo trovo
        while(temp->next != NULL & temp->codice != c){
            temp=temp->next;
        }
        // E ritorno il suo puntatore
        if(temp->codice == c) return temp;
    }

    return NULL;
}

// Questa funzione prende una lista e raggruppa gli elementi
// con lo stesso "codice" , sommandone le "quantità"
struct s_elem *raggruppa(struct s_elem **lista){
    // Creo una nuova lista e un puntatore temporaneo
    struct s_elem *newlist = NULL;
    struct s_elem *temp = *lista;

    // Se la lista è vuota, non c'è nulla da raggruppare
    if(*lista == NULL) {
        printf("La lista è vuota");
        return NULL;
    }
    else {
        // Altrimenti scorro la lista
        while(temp != NULL){
            // Per ogni nodo creo un altro nodo "samechar" che è il
            // risultato di cercaelem ovvero il puntatore al primo
            // elemento con lo stesso codice del nodo preso in considerazione
            struct s_elem *samechar = cercaelem(&newlist,temp->codice);
            // Se non è nullo
            if(samechar != NULL){
                // All'elemento appena creato vado ad aggiungere la quantità
                // del suo nodo "gemello" appena preso in consid.
                samechar->quantita += temp->quantita;
            }
            else{
                // Se invece è nullo, pazienza
                // aggiungo semplicemente alla lista l'elemento
                char codice = temp->codice;
                int quantita = temp->quantita;
                struct s_elem *nodo = creaelem(codice,quantita);
                inseriscicoda(&newlist,nodo);
            }
            // solito comando per scorrere la lista
            temp=temp->next;
        }
    }
    return newlist;
}

// Questa funzione prende una lista e un codice e restituisce
// una lista togliendo tutti gli elementi con quel codice

struct s_elem *filtralista(struct s_elem *lista, char codice){
    // Creo una nuova lista e un punt. temp.
    struct s_elem *filtered = NULL;
    struct s_elem *temp = lista;

    // Se è vuota non ce ne facciamo niente
    if(lista == NULL){
        return NULL;
    }
    else{
        // Se non è vuota scorro
        while(temp != NULL){
            // E se il nodo non contiene quel codice, lo aggiungo alla nuova lista
            if(temp->codice != codice){
                char codice = temp->codice;
                int quantita = temp->quantita;
                struct s_elem *nodo = creaelem(codice,quantita);
                inseriscicoda(&filtered,nodo);
            }
            // Ovviamente, se contiene quel codice, viene ignorato            
            temp = temp->next;  
        }
    }
    return filtered;
}



// Questa funzione prende in input un puntatore ad una lista
// e ne cancella tutti i nodi con quantità divisibile per "val"
void cancellaNodo(struct s_elem **lista , int val){
    // Dichiaro il mio solito puntatore temporaneo
    struct s_elem *temp = *lista;
    // E un altro puntatore che mi servirà per tenere traccia
    // Dell' elemento precedente rispetto a quello considerato
    struct s_elem *prec = NULL;

    // Come al solito, se non c'è nulla, ce ne andiamo
    if(temp == NULL){
        return;
    }
    else{
        // Altrimenti andiamo a ciclare la lista
        while(temp != NULL){
            // Se l'elemento rispetta i parametri
            if(temp->quantita % val == 0 && temp->quantita != 0){
                // Divido i tre casi:
                // Se sto considerando il primo elemento della lista...
                if(temp == *lista){
                    // La nuova testa della lista è il suo next
                    *lista = temp->next;
                    // Libero la memoria 
                    free(temp);
                    // E riassegno al punt. temp. la testa
                    // per permettergli di continuare il giro
                    temp = *lista;
                }
                //... oppure l'ultimo
                else if(temp->next == NULL){
                    // Mi assicuro che il mio precedente non punti più a me

                    prec->next=NULL;
                    // Qui semplicemente libero la memoria
                    free(temp);
                }
                // ...oppure uno in mezzo
                else{
                    // All'elemento precedente vado ad assegnare il mio
                    // next, in modo da "saltare" il mio nodo
                    prec->next = temp->next;
                    // Poi libero la memoria
                    free(temp);
                    // E riassegno al mio punt. temp. il valore successivo
                    // per poter continuare il giro
                    temp = prec->next;
                }
            }
            // All'elemento precedente associo l'attuale
            prec = temp;
            // E all'attuale associo il successivo
            temp = temp->next;
        }
    }
}

// Questa funzione prende una lista e la divide in due sottoliste
// una per i pari e una per i dispari , non prima di aver tolto
// di mezzo tutti i numeri con quantità divisibile per 5
void dividilista(struct s_elem **originale, struct s_elem **lp ,struct s_elem **ld){
    // Solito puntatore temporaneo
    struct s_elem *temp = *originale;
    if(originale != NULL){
        // Chiamo la funzione precedente per togliere chi non serve
        cancellaNodo(&temp,5);
        // E ciclo la lista "ripulita"
        while(temp != NULL){
            // Se la quantità è pari lo butto nella lista pari
            if(temp->quantita % 2 == 0){
                char codice = temp->codice;
                int quantita = temp->quantita;
                struct s_elem *nodo = creaelem(codice,quantita);
                inseriscicoda(lp,nodo);
            }
            // Altrimenti nei dispari
            else if(temp->quantita % 2 == 1){
                char codice = temp->codice;
                int quantita = temp->quantita;
                struct s_elem *nodo = creaelem(codice,quantita);
                inseriscicoda(ld,nodo);
            }
            // E vado avanti
            temp = temp->next;
        }
        // Mi assicuro di ripulire la lista originale come richiesto
        // dalla traccia
        *originale = NULL;
    }
}

// Questa funzione prende una lista, un nome di file e un
// "tipofile" (testuale o binario) e scrive sul file indicato la lista passata
int salvalista(struct s_elem *lista , char path[PATH_LEN], t_file tipofile){
    FILE *fp;
    struct s_elem *temp = lista;
    char mod[5];

    // Una semplice if/else per capire se scrivere in testuale o in binario
    if (tipofile == txt) strcpy(mod,"w");
    else if (tipofile == bin) strcpy(mod,"wb");
    else {
        // Se non è nessuno dei due me ne esco subito
        printf("Inserire una modalità di scrittura valida txt/bin\n");
        return -1;
    }
    
    // Apro il file con la modalità indicata
    fp = fopen(path,mod);
    if (fp == NULL){
        // Se ci sono errori esco 
        printf("Errore nell'apertura del file.");
        return -1;
    }

    // Scorro la lista
    while(temp != NULL){
        // Scrittura testuale
        if(tipofile == txt){
            // fprintf() ritorna il numero di caratteri scritti
            int ok = fprintf(fp,"%c %d\n",temp->codice,temp->quantita);
            // e quindi se ne scrive 0 qualche problema ci sarà...
            if(ok == 0){
                printf("Errore nella scrittura");
                return -1;
            }
        }
        // Scrittura binaria
        else{
            // Stessa roba di sopra
            int ok = fwrite(temp, sizeof(struct s_elem), 1, fp);
            if(ok == 0){
                printf("Errore nella scrittura binaria");
                return -1;
            }
        }
        // Avanzo nella lista come al solito
        temp=temp->next;
    }
    // Avverto in console che tutto va bene, chiudo file e ritorno 0 come da traccia
    printf("\nLista salvata su file");
    fclose(fp);
    return 0;
}

// Questa funzione prende in input un puntatore ad una lista,
// un nome file e un tipofile come la funzione precedente
// legge da file e mette il contenuto nella lista passata;
int caricalista(struct s_elem **lista, char path[PATH_LEN], t_file tipofile){
    FILE *fp;
    char mod[5];

    // Dichiaro delle variabili che serviranno dopo
    char codice;
    int quantita;
    // E una struttura temporanea che inizializzo ad un valore
    // a caso, che verrà comunque sovrascritto, lo faccio
    // per allocare la memoria grazie al malloc contenuto
    // nella funzione creaelem()
    struct s_elem *temp = creaelem('A',0);
    
    // Stessa roba dell'altra funzione per prendere il tipo di lettura
    if (tipofile == txt) strcpy(mod,"r");
    else if (tipofile == bin) strcpy(mod,"rb");
    else {
        printf("Inserire una modalità di scrittura valida txt/bin\n");
        return -1;
    }
    
    // Apro file come già visto prima
    fp = fopen(path,mod);
    if (fp == NULL){
        printf("Errore nell'apertura del file.");
        return -1;
    }

    // Lettura testuale
    if(tipofile == txt){
        // Con un do while giro finchè non finisce il file (!feof)
        do{
            // fscanf prende i dati dal file
            fscanf(fp,"%c %d\n", &codice,&quantita);
            // creo il nodo con i dati appena presi
            struct s_elem *elemento = creaelem(codice,quantita);
            // se tutto è andato bene lo metto in coda alla mia lista
            if(elemento != NULL) inseriscicoda(lista,elemento);
            // altrimenti ritorno -1
            else return -1;
        }while(!feof(fp));
    }
    //Lettura binaria
    else{
        // Finchè il numero di caratteri letti > 0
        while(fread(temp,sizeof(struct s_elem),1,fp) >0){
            // Creo una struttura con i dati letti
            struct s_elem *elemento = creaelem(temp->codice,temp->quantita);
            // E la carico nella mia lista
            if(elemento != NULL) inseriscicoda(lista,elemento);
            else return -1;

        }
    }
    // Libero la memoria utilizzata , chiudo il file e ritorno 0 come da traccia
    free(temp);
    fclose(fp);
    return 0;
}

int main(){
    // Roba strana di C per fare i numeri random
    srand(time(NULL));

    // Dichiaro le mie variabili e tutte le liste necessarie
    int i;
    struct s_elem *lista1 = NULL;
    struct s_elem *lista2 = NULL;
    struct s_elem *lista3 = NULL;
    struct s_elem *lista4 = NULL;
    struct s_elem *lp = NULL;
    struct s_elem *ld = NULL;
    struct s_elem *lp_c = NULL;
    struct s_elem *ld_c = NULL;

    // Inserimento in testa in lista 1
    for(i=0;i<DIM;i++){
        char codice = 'A' + rand() % ('Z' - 'A' + 1); //codice A-Z
        int quantita = rand() % 10; //quantita' 0-9
        struct s_elem *nodo = creaelem(codice,quantita);
        inseriscitesta(&lista1,nodo);
    }
    stampalista(lista1,"Lista1");

    // Inserimento in coda in lista 2
    for(i=0;i<DIM;i++){
        char codice = 'A' + rand() % ('Z' - 'A' + 1); //codice A-Z
        int quantita = rand() % 10; //quantita' 0-9
        struct s_elem *nodo = creaelem(codice,quantita);
        inseriscicoda(&lista2,nodo);
    }
    stampalista(lista2,"Lista2");

    // Caricamento lista3 con raggruppamento da lista1
    lista3 = raggruppa(&lista1);
    stampalista(lista3,"Lista3");

    // Chiedo carattere da eliminare e chiamo filtralista
    char toDelete;    
    printf("\n\nInserire un carattere da eliminare: ");
    scanf("%c",&toDelete);
    lista4 = filtralista(lista1,toDelete);
    stampalista(lista4,"Lista 4");

    // Chiamo il dividilista
    dividilista(&lista3,&lp,&ld);
    stampalista(lp,"Lista pari");
    stampalista(ld,"Lista dispari");
    stampalista(lista3,"Lista3");

    // Salvo le liste su file come da traccia
    salvalista(lp,"pari.txt",txt);
    salvalista(ld,"dispari.bin",bin);

    // Ricarico le liste dai file in due nuove liste
    // lp_c e ld_c e poi le stampo
    caricalista(&lp_c,"pari.txt",txt);
    stampalista(lp_c,"Lista pari caricata");
    caricalista(&ld_c,"dispari.bin",bin);
    stampalista(ld_c,"Lista dispari caricata");

    return 0;
}
