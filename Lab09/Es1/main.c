#include <stdio.h>
#include <stdlib.h>


typedef struct att{
    int inizio;
    int fine;
} att;

int checksolmax(att *sol, att *solmax, int i){
    int sum_sol = 0, sum_solmax = 0;        //somme delle durate
    if(i==1) {                    //sol. lunghezza 1
        if( (solmax->fine - solmax->inizio) < (sol->fine - sol->inizio))
            return 1;
        else return 0;
    }
    else {
        for (size_t j = 0; j < i; j++) {
            sum_sol += sol[j].fine - sol[j].inizio;
            sum_solmax += solmax[j].fine - solmax[j].inizio;
        }
        if (sum_solmax - sum_sol < 0)    //la nuova soluzione ha durata totale maggiore
            return 1;
        else return 0;
    }
}
int checkcompatibilita(att att1, att att2){       //funzione che prende due attività e controlla che siano compatibili
    if(att1.inizio < att2.inizio && att1.fine <= att2.inizio) return 1;
    else return 0;
}
int pruning(att *sol, att a, int j, int pos){
    if(j==0)            //scelta iniziale
        return 1;
    else {
        if(checkcompatibilita(sol[pos-1], a))       //confronto tra scelta precedente e quella attuale
            return 1;
        else return 0;
    }
}
int powerset_r(att *val, int n, att* sol, att* solmax, int i, int pos, int start) {
    int count = 0, j;
    if (pos == i) {              //terminazione, raggiunto il n. di insiemi max per questo giro ricorsivo
        if(checksolmax(sol, solmax, i)) {            //controllo che la soluzione sia max
            for(size_t k=0; k<i; k++){
                solmax[k] = sol[k];
            }
        }
        return i;
    }
    for (j = start; j < n; j++) {
        if (pruning(sol,val[j], j, pos)) {    //controllo che l'attività che viene scelta sia compatibile con le altre scelte in precedenza
            sol[pos] = val[j];              //scelgo un' attività
            i = powerset_r(val, n, sol, solmax, i, pos + 1, j + 1);
        }
    }
    return i;
}
void attSel(int N, att *v){     //funzione wrapper
    att *sol;                  //vettore soluzione temporaneo
    att *solmax = calloc(N, sizeof(att));      //vettore soluzione max richiesto
    int length = 0;         //lunghezza soluzione max

    printf(":;\n");     //insieme vuoto
    for(size_t i=1; i<N; i++) {
        sol = malloc(i * sizeof(att));
        length = powerset_r(v, N, sol, solmax, i, 0, 0);
        free(sol);
    }
    printf("Il sottoinsieme di attivita' che massimizza la durata totale e' : \n");
    for(size_t j=0; j<length; j++){
        printf("(%d, %d) ", solmax[j].inizio, solmax[j].fine);
    }
    printf("\n");
    free(solmax);
}
int main() {
    setbuf(stdout, NULL);
    FILE *fp = fopen("att.txt", "r");
    att *v;
    int n_att;

    fscanf(fp, "%d", &n_att);
    v = malloc(n_att * sizeof(att));
    for(size_t i=0; i<n_att; i++)
        fscanf(fp, "%d %d", &v[i].inizio, &v[i].fine);
    fclose(fp);

    attSel(n_att, v);
    free(v);
    return 0;
}
