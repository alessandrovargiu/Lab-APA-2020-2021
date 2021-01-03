#ifndef ES3_PG_H
#define ES3_PG_H
#include "inventario.h"

typedef struct equip {
    int inUso;
    Inventario *tabInv[8];
} Equip;
typedef struct pg {
    char ID[10];
    char nome[max];
    char classe[max];
    Stats s;
    Equip eq;
} Pg;

typedef struct node *link;
struct node {
    Pg val;
    link next;
};

link newNode(Pg val, link next);
link listDelKey(link h, char *code);
void listInsTail(link *h, Pg val);

void freememory_pg(link *h);
void printlist(link h);
void calcstats(link *h);
void addequip(link x, tabInv **inv);
void deleteequip(link x);
void changeequip(link *head, tabInv **inv);
void ricerca_pg(link *head);
void loadpg_keyboard(link *head);
void delete_pg(link *head);
void loadpg(link *head);


#endif //ES3_PG_H
