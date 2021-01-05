#include <stdio.h>
//1o_es1_0809
struct Tfornitore {int codice; char nome[20];};
struct Tindice {int codice; int pos;};
struct Tfornitore fornitore;
struct Tindice indice;
int main(){
    FILE *PtrIndice, *PtrFornitore;
    int codice, trovato=0;
    PtrIndice = fopen("indice.dat", "rb");
    if (PtrIndice == NULL)
        printf("errore in aperura di indice.dat\n");
    else{
        printf("valore di codice: ");
        scanf("%d",&codice);
        while (!feof(PtrIndice)&& (trovato==0)){
            fread(&indice, sizeof(struct Tindice), 1,PtrIndice);
            if (indice.codice == codice){
                trovato=1;
            }
        }
        if (trovato==0){
            printf("codice non trovato");
        }
        else{
            printf("codice trovato a pos: %d\n",indice.pos);
            PtrFornitore = fopen("fornitore.dat", "r");
            if (PtrFornitore == NULL){
                printf("errore in aperura di fornitore.dat\n");
            }
            else{
                fseek(PtrFornitore, indice.pos, SEEK_SET);
                fread(&fornitore, sizeof(struct Tfornitore), 1,PtrFornitore);
                printf("codice: %d\nnome: %s",fornitore.codice,fornitore.nome);
            }
        }
    fclose(PtrIndice);
    fclose (PtrFornitore);
    }
}
