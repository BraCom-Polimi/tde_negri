#include <stdio.h>
#include<stdlib.h>
struct Tfornitore {int codice; char nome[20];};
struct Tindice {int codice; int pos;};
struct Tfornitore fornitore;
struct Tindice indice;
int main(){
    FILE *PtrIndice, *PtrFornitore;
    PtrFornitore = fopen("fornitore.dat", "wb");
    PtrIndice = fopen("indice.dat", "wb");
    if (PtrIndice == NULL||PtrFornitore==NULL)
        printf("errore in aperura \n");
    else{
        while(fornitore.codice!=99){
            printf("codice: ");
            scanf("%d",&fornitore.codice);
            indice.codice=fornitore.codice;
            printf("nome: ");
            scanf("%s",&fornitore.nome);
            fwrite(&fornitore,sizeof(struct Tfornitore),1,PtrFornitore);
            fseek(PtrFornitore,0,SEEK_CUR);
            indice.pos=ftell(PtrFornitore)-24;
            printf("%\n\t\t%d\n",indice.pos);
            fwrite(&indice,sizeof(struct Tindice),1,PtrIndice);
            //fflush(st)
        }
    //fclose(PtrIndice);
    fclose (PtrFornitore);
    }
}
