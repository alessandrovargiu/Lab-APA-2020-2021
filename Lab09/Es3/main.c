#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "pg.h"
#define max 50

typedef enum command {
    caricapg, caricainv, aggiungipg, eliminapg, ricercapg, ricercaobj, modificaeq, statspg, stampa, fine
} command;

command leggiComando(){
    command c;
    char *tabella[fine+1] = {
            "caricapg", "caricainv", "aggiungipg", "eliminapg", "ricercapg", "ricercaobj", "modificaeq", "statspg",  "stampa", "fine"
    };
    char cmd[max];
    printf("\nComandi:\ncaricapg -> crea elenco pg da file\ncaricainv -> crea inventario da file\naggiungipg -> aggiungi personaggio da tastiera"
           "\nricercapg -> ricerca un personaggio per codice\nricercaobj -> ricerca oggetto per nome e mostra i suoi stats\nmodificaeq -> aggiungi/rimuovi un oggetto dall'inventario\n"
           "statspg -> visualizza le statistiche di un personaggio e il suo equip\nstampa -> stampa lista PG\nfine -> fine programma\n");
    scanf("%s", cmd);
    c = caricapg;
    while(c<fine && strcmp(cmd, tabella[c])!=0)
        c++;
    return c;
}
int main() {
    setbuf(stdout, NULL);
    link head = NULL;
    tabInv **inv = malloc(sizeof(tabInv*));     //da modificare

    while(1) {
        command c = leggiComando();
        switch (c){
            case caricapg:
                loadpg(&head);
                break;
            case caricainv:
                loadinv(inv);
                break;
            case aggiungipg:
                loadpg_keyboard(&head);
                break;
            case eliminapg:
                delete_pg(&head);
                break;
            case ricercapg:
                ricerca_pg(&head);
                break;
            case ricercaobj:
                ricercaobject(inv);
                break;
            case modificaeq:
                changeequip(&head, inv);
                break;
            case statspg:
                calcstats(&head);
                break;
            case stampa:
                printlist(head);
                break;
            case fine:
                freememory_pg(&head);
                freememory_inv(&inv);
                return 0;
            default:
                printf("\nComando errato.");
                break;
        }
    }
}
