#include <stdio.h>
#include <stdlib.h>

typedef struct tessera{
    char color_v, color_h;      //colori verticale e orizzontale
    int score_v, score_h;       //punteggio vert. e orizz.
} Tessera;
typedef struct b{
    Tessera t;
    int r;      //rotazione
} Board;

int checksol(Board **init, int r, int c){         //calcola il punteggio di una scacchiera per poterlo confrontare con la sol
    int totr = 0, totc = 0;      //punteggi riga e colonna
    int pr = 0, pc = 0;     //punteggi parziali righe e colonne
    char color;



    //calcolo punteggi riga
    for(size_t i=0; i<r; i++){
        color = init[i][0].t.color_h;  //colore del primo elemento della riga corrente
        pr += init[i][0].t.score_h;
        for(size_t j=1; j<c; j++){      //la prima colonna è gia' controllata
            if(init[i][j].t.color_h != color) {
                pr = 0;
                break;      //prossima riga
            }
            else
                pr += init[i][j].t.score_h;
        }
        totr += pr;
        pr = 0;
    }
    //calcolo punteggi colonna
    for(size_t j=0; j<r; j++){
        color = init[0][j].t.color_v;  //colore del primo elemento della colonna corrente
        pc += init[0][j].t.score_v;
        for(size_t i=1; i<c; i++){      //la prima riga è gia' controllata
            if(init[i][j].t.color_v != color) {
                pc = 0;
                break;      //prossima colonna
            }
            else
                pc += init[i][j].t.score_v;
        }
        totc += pc;
        pc = 0;
    }

    return totr + totc;         //punteggio totale
}
Tessera ruota_tessera(Tessera t){     //effetto una rotazione dei tubi della tessera
    int tmp;
    char cmp;
    cmp = t.color_v;
    t.color_v = t.color_h;
    t.color_h = cmp;
    tmp = t.score_v;
    t.score_v = t.score_h;
    t.score_h = tmp;
    return t;
}
void perm_sempl(int i, int j, Tessera *val, Board **init, Board **sol, int *max, int **mark, int r, int c) {
    int k, tot = 0, n = r*c;        //k usato per scorrere il vettore mark (dimensione r*c)
    if (i == r) {     //terminazione
        tot = checksol(init, r, c);
        if(tot > *max){ //se ho trovato una soluzione migliore la copio in sol
            for(size_t p=0; p<r; p++){
                for(size_t q=0; q<c; q++){
                    sol[p][q].t = init[p][q].t;
                }
            }
            *max = tot;
        }
        return;
    }

    if(init[i][j].r != -1) {            //se è uguale a -1 questa casella fa parte della config. iniziale e passo alla prossima
        for (k = 0; k < r * c; k++) {     //r*c = num. tessere
            if (mark[0][k] == -1 || mark[0][k] == 1) {
                continue;
            } else {
                mark[0][k] = 1;         //prendo la tessera k non ruotata
                mark[1][k] = 1;
                init[i][j].t = val[k];
                if (j == c - 1)
                    perm_sempl(i + 1, 0, val, init, sol, max, mark, r, c);
                else {
                    perm_sempl(i, j + 1, val, init, sol, max, mark, r, c);
                }
                mark[0][k] = 0;     //la rimetto a posto
                mark[1][k] = 0;
                if (mark[1][k] == 1 || mark[1][k] == -1) {  //la tessera ruotata è gia' stata presa oppure è una di quelle fisse
                    continue;
                } else {
                    mark[1][k] = 1;     //prendo la tessera ruotata
                    mark[0][k] = 1;
                    init[i][j].t = ruota_tessera(val[k]);
                    if (j == c - 1)
                        perm_sempl(i + 1, 0, val, init, sol, max, mark, r, c);
                    else
                        perm_sempl(i, j + 1, val, init, sol, max, mark, r, c);
                    mark[1][k] = 0;     //rimetto a posto
                    mark[0][k] = 0;
                }
            }
        }
    }
    else{
        if(j == c-1)
            perm_sempl(i+1, 0, val, init, sol, max, mark, r, c);
        else
            perm_sempl(i, j+1, val, init, sol, max, mark, r, c);
    }
}
void perm_wrapper(Tessera *t, Board **b, int **mark, int r, int c){
    Board **sol=malloc(r * sizeof(Board*));
    int max = 0;
    for(size_t i=0; i<r; i++)
        sol[i] = malloc(c * sizeof(Board));

    perm_sempl(0, 0, t, b, sol, &max, mark, r, c);

    printf("Soluzione di punteggio massimo %d: \n", max);
    for(size_t i=0; i<r; i++){
        for(size_t j=0; j<c; j++){
            printf("(%c %d/%c %d) ", sol[i][j].t.color_h, sol[i][j].t.score_h, sol[i][j].t.color_v, sol[i][j].t.score_v);
        }
        printf("\n");
    }
}
Board **readBoard(Tessera *t, int **mark, int *r, int *c){
    FILE *fp = fopen("board.txt", "r");
    int ti, rot;  //ti è l'indice delle tessere, rot l'indice di rotazione
    Board **b;

    fscanf(fp, "%d %d", r, c);
    b = malloc(*r * sizeof(Board*));       //allocazione scacchiera2D
    for(size_t i=0; i<*c; i++)
        b[i] = malloc(*c * sizeof(Board));

    for(size_t i=0;i<*r; i++) {
        for (size_t j = 0; j < *c; j++) {
            fscanf(fp, "%d/%d", &ti, &rot);
            if (ti == -1) {             //casella vuota
                b[i][j].r = 0;
            } else {
                if(rot == 0) {
                    b[i][j].t = t[ti];         //la casella della scacchiera contiene il puntatore alla tessera
                }
                else {
                    b[i][j].t = ruota_tessera(t[ti]);
                }
                b[i][j].r = -1;
                mark[0][ti] = -1;       //questa tessera fa parte della config. iniziale
                mark[1][ti] = -1;       // e non potra' essere utilizzata
            }
        }
    }

    fclose(fp);
    return b;
}
Tessera *readtiles(int ***mark){
    FILE *fp = fopen("tiles.txt", "r");
    int n_tiles;
    Tessera *t;

    fscanf(fp, "%d\n", &n_tiles);
    *mark = malloc(2 * sizeof(int *));  //2 righe, una per ogni tipo di rotazione
    for(size_t i=0; i<2; i++)
        (*mark)[i] = calloc(n_tiles, sizeof(int));     //n_tiles numero di colonne

    t = malloc(n_tiles * sizeof(Tessera));
    for(size_t i=0; i<n_tiles; i++){
        fscanf(fp, "%c %d %c %d\n", &t[i].color_h, &t[i].score_h, &t[i].color_v, &t[i].score_v);
    }
    fclose(fp);
    return t;
}
int main() {
    setbuf(stdout, NULL);
    int **mark = malloc(sizeof(int *));
    int r,c;
    Tessera *t = readtiles(&mark);

    Board **b = readBoard(t, mark, &r, &c);

    perm_wrapper(t, b, mark, r, c);

    return 0;
}
