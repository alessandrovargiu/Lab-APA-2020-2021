#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
} Arco ;
typedef struct {
    int N;      //numero vertici
    Arco *archi;
} Grafo;

int BinSearch(int *v, int l, int r, int k) {    //il vettore sol. si presenta ordinato grazie alle comb. semplici --> uso la ricerca binaria
    int m;

    while(l<=r) {
        m =  (l+r)/2;
        if(v[m] == k)
            return(m);
        if(v[m] < k)
            l = m+1;
        else
            r = m-1;
    }
    return -1;
}
int check_sol(Grafo *val, int *sol, int na, int i){     // i rappresenta la grandezza del vettore sol
    for(size_t j=0; j<na; j++){
        if(BinSearch(sol, 0, i, val->archi[j].u) == -1 && BinSearch(sol, 0, i, val->archi[j].v) == -1){
            return 0;
        }
    }
    return 1;
}
int powerset_r(Grafo *val, int n, int* sol, int i, int pos, int start, int na){
    int count = 0, j;
    if (pos == i){
        if(check_sol(val, sol, na, i)) {        //controllo se l'insieme di vertici corrente soddisfa la condizione di vertex cover
            printf("{ ");
            for (j = 0; j < i; j++)
                printf("%d ", sol[j]);
            printf("}\n");
            return 1;
        }
        else return 0;              //soluzione esclusa
    }
    for (j = start; j < n; j++){
        sol[pos] = j;
        count += powerset_r(val, n, sol, i, pos+1, j+1, na);
    }
    return count;
}

int powerset_comb_semp(Grafo *val, int n, int *sol, int na){
    int count = 0, i;
    printf("{ }\n");
    count++;
    for(i = 1; i <= n; i++){
        sol = malloc(i * sizeof(int));      //adatto il vettore soluzione alle comb. semplici
        count += powerset_r(val, n, sol, i, 0, 0, na);
        free(sol);
    }
    return count;
}

Grafo *leggiGrafo(FILE *fp, int *nv, int *na){
    fp=fopen("grafo.txt", "r");
    Grafo *g;

    fscanf(fp, "%d %d", nv, na);
    g = malloc(sizeof(Grafo));          //grafo allocato
    g->N = *nv;
    g->archi = malloc(*na * sizeof(Arco));      //archi allocati
    for(size_t i=0; i<*na; i++)
        fscanf(fp, "%d %d", &g->archi[i].u, &g->archi[i].v);   //archi salvati
    fclose(fp);
    return g;
}
int main() {
    setbuf(stdout, NULL);
    Grafo *g;
    FILE *fp;
    int nv, na;
    int *sol;              //ogni casella contiene un intero che rappresenta un vertice
    g = leggiGrafo(fp, &nv, &na);
    powerset_comb_semp(g, nv, sol, na);
    return 0;
}
