#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"
#include "inventario.h"



link newNode(Pg val, link next){
    link x = malloc(sizeof(*x));    //alloco nodo
    if(x==NULL) return NULL;    //allocazione non riuscita
    //creazione
    x->val = val;
    x->next = next;
    return x;
}
void listInsTail(link *h, Pg val){
    link x=*h;
    if(x==NULL) *h = newNode(val, NULL);    //se il puntatore alla testa è nullo ritorno il primo nodo
    else {
        for (; x->next != NULL; x = x->next);  //altrimenti scorro all'ultimo nodo
        x->next = newNode(val, NULL);   //e inserisco in coda
    }
}
link listDelKey(link h, char *code){
    link x, p;
    if(h==NULL) return NULL;
    for(x=h, p=NULL; x!=NULL; p=x, x=x->next){
        if(!strcmp(x->val.ID, code)){
            if(x==h) h=x->next;
            else p->next = x->next;
            free(x->val.eq.tabInv);
            free(x);
            break;
        }
    }
    return h;
}

void freememory_pg(link *h){
    if(h!=NULL) {
        link *x;
        for (x = h; *x != NULL; (*x) = (*x)->next) {          //lista personaggi
            free(x);
        }
    }
}
void printlist(link h){
    link x;
    for(x=h; x!=NULL; x=x->next){
        printf("%s %s %s \n", x->val.ID, x->val.nome, x->val.classe);
    }
}
void calcstats(link *h){
    char nome[max];
    link x;
    int hp=0, mp=0, atk=0, def=0, mag=0, spr=0;         //contengono le somme delle relative stats
    printf("\nInserire il nome del personaggio di cui visualizzare le statistiche: \n");
    printlist(*h);
    scanf("%s", nome);
    for(x=*h; x!=NULL;  x=x->next) {     //attraverso lista per trovare il pg
        if(!strcmp(x->val.nome, nome)){
            //parametri base
            hp = x->val.s.hp;
            mp = x->val.s.mp;
            atk = x->val.s.atk;
            def = x->val.s.def;
            mag = x->val.s.mag;
            spr = x->val.s.spr;
            for(size_t i=0; i<x->val.eq.inUso; i++){        //scorro equipaggiamento
                hp+=x->val.eq.tabInv[i]->s.hp;
                mp+=x->val.eq.tabInv[i]->s.mp;
                atk+=x->val.eq.tabInv[i]->s.atk;
                def+=x->val.eq.tabInv[i]->s.def;
                mag+=x->val.eq.tabInv[i]->s.mag;
                spr+=x->val.eq.tabInv[i]->s.spr;
            }
            break;              //uscita non strutturata, per evitare di scorrere la lista inutilmente
        }
    }
    if(hp<0) hp = 0;
    if(mp<0) mp = 0;
    if(atk<0) atk = 0;
    if(def<0) def = 0;
    if(mag<0) mag = 0;
    if(spr<0) spr = 0;
    printf("\nLe statistiche di %s sono : (hp) %d, (mp) %d, (atk) %d, (def) %d, (mag) %d, (spr) %d\n", nome, hp, mp, atk, def, mag, spr);
    if(x->val.eq.inUso == 0) printf("L'equipaggiamento di %s e' vuoto!\n", nome);
    else {
        printf("L'equipaggiamento di %s e' composto da : ", nome);
        for (size_t i = 0; i < x->val.eq.inUso; i++) {
            printf("\n%s", x->val.eq.tabInv[i]->nome);
        }
    }
}
void addequip(link x, tabInv **inv){
    char nome[max];

    if(x->val.eq.inUso == 8) {
        printf("\nEquipaggiamento pieno! rimuovere un oggetto.");
        return;
    }
    printf("\nInserire nome dell'oggetto da equipaggiare: ");
    scanf("%s",nome);
    for(size_t i=0; i<(*inv)->n_inv; i++){
        if(strcmp((*inv)->inv[i].nome, nome) == 0) {     //trovato oggetto nell'inventario
            x->val.eq.tabInv[x->val.eq.inUso] = &(*inv)->inv[i];
            x->val.eq.inUso++;
            printf("\nOggetto equipaggiato correttamente.\n");
            return;
        }
    }
    printf("\nOggetto non trovato.\n");
}
void deleteequip(link x){
    char nome[max];

    if(x->val.eq.inUso == 0){
        printf("\nEquipaggiamento vuoto! inserire un oggetto.");
        return;
    }
    printf("\nInserire nome dell'oggetto da rimuovere ");
    scanf("%s", nome);
    for(size_t i=0; i<x->val.eq.inUso; i++){
        if(strcmp(x->val.eq.tabInv[i]->nome, nome) == 0){
            x->val.eq.tabInv[i] = NULL;             //oggetto rimosso
            x->val.eq.inUso--;
            printf("\nOggetto rimosso.\n");
            return;
        }
    }
    printf("\nOggetto non trovato.\n"); //la ricerca nel for non ha avuto successo
}
void changeequip(link *head, tabInv **inv){
    char ID[max];
    int flag;
    link x;
    printf("\nInserire l'ID del personaggio a cui modificare l'equipaggiamento: \n");
    scanf("%s", ID);
    for(x=*head; x!=NULL ; x=x->next){              //attraversamento lista
        if(strcmp(x->val.ID, ID) == 0) break;
    }
    while(1){
        printf("\nPremi 1 per aggiungere un oggetto, 2 per rimuoverlo, 0 per terminare: ");
        scanf("%d", &flag);
        switch(flag){
            case 0:
                return;
            case 1:
                addequip(x, inv);
                break;
            case 2:
                deleteequip(x);
                break;
            default:
                printf("\nScelta errata.");
                break;
        }
    }
}
void ricerca_pg(link *head){
    link x;
    char code[max];
    printf("\nInserire codice del personaggio da cercare: \n");
    scanf("%s", code);
    for(x=*head; x!=NULL; x = x->next)
        if(!strcmp(x->val.ID, code)){
            printf("Personaggio trovato! :\n");
            printf("%s %s %s\n", x->val.ID, x->val.nome, x->val.classe);
            return;
        }
    printf("Personaggio non trovato.\n");
}
void delete_pg(link *head){
    char code[max];
    printf("\nInserire il codice del personaggio da eliminare: \n");
    scanf("%s", code);
    if(listDelKey(*head, code) != NULL)
        printf("\nEliminazione eseguita correttamente.");
    else printf("\nErrore durante la cancellazione.");

}
void loadpg_keyboard(link *head){
    Pg *val = malloc(sizeof(Pg));       //struttura personaggio
    val->eq.inUso = 0;
    printf("\nInserire codice, nome, classe e statistiche del personaggio: \n");
    scanf("%s %s %s %d %d %d %d %d %d", val->ID, val->nome, val->classe,
          &val->s.hp, &val->s.mp, &val->s.atk, &val->s.def, &val->s.mag, &val->s.spr);
    listInsTail(head, *val);            //inserimento in coda
}
void loadpg(link *head){
    FILE *fp;
    char nomefile[max];
    Pg *val = malloc(sizeof(Pg));       //allocazione struttura personaggio
    val->eq.inUso = 0;
    printf("\nInserisci il nome del file da leggere: ");
    scanf("%s", nomefile);
    fp = fopen(nomefile, "r");
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", val->ID, val->nome, val->classe,
                 &val->s.hp, &val->s.mp, &val->s.atk, &val->s.def, &val->s.mag, &val->s.spr) != EOF){
        listInsTail(head, *val);
    }
    fclose(fp);
}
