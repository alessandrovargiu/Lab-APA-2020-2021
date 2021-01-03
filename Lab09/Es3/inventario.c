#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inventario.h"



void freememory_inv(tabInv ***inv){     //libero memoria dinamica alla fine del programma
    free((**inv)->inv);             //libero inventario
    free(**inv);
}
void loadinv(tabInv **inv){
    FILE *fp;
    char nomefile[max];
    *inv = malloc(sizeof(tabInv));

    printf("\nInserisci il nome del file da cui prendere l'inventario: ");
    scanf("%s", nomefile);
    fp = fopen(nomefile, "r");
    fscanf(fp, "%d", &(*inv)->n_inv);
    (*inv)->inv = malloc((*inv)->n_inv * sizeof(Inventario)); //vettore inventario
    for(size_t i=0; i<(*inv)->n_inv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", (*inv)->inv[i].nome, (*inv)->inv[i].tipo, &(*inv)->inv[i].s.hp, &(*inv)->inv[i].s.mp, &(*inv)->inv[i].s.atk, &(*inv)->inv[i].s.def, &(*inv)->inv[i].s.mag, &(*inv)->inv[i].s.spr);
    }
    fclose(fp);
}
void ricercaobject(tabInv **inv){
    char nome[max];
    printf("Inserire il nome dell'oggetto da ricercare\n");
    scanf("%s", nome);

    for(size_t i=0; i<(*inv)->n_inv; i++)
        if(!strcmp(nome, (*inv)->inv[i].nome)){
            printf("Oggetto trovato!\n");
            printf("%s %s %d %d %d %d %d %d\n", (*inv)->inv[i].nome, (*inv)->inv[i].tipo, (*inv)->inv[i].s.hp,
                   (*inv)->inv[i].s.mp, (*inv)->inv[i].s.atk, (*inv)->inv[i].s.def, (*inv)->inv[i].s.mag, (*inv)->inv[i].s.spr);
            return;
        }
    printf("Oggetto non trovato!");
}
