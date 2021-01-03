#ifndef ES3_INVENTARIO_H
#define ES3_INVENTARIO_H
#define max 50

typedef struct stats {
    int hp, mp, atk, def, mag, spr;
} Stats;
typedef struct oggetto {
    char nome[max];
    char tipo[max];
    Stats s;
} Inventario;
typedef struct tabInv {
    Inventario *inv;
    int n_inv;
} tabInv;

void freememory_inv(tabInv ***inv);
void loadinv(tabInv **inv);
void ricercaobject(tabInv **inv);

#endif //ES3_INVENTARIO_H
