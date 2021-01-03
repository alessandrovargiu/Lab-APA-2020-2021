#include <stdio.h>
#include <stdlib.h>

typedef struct att{
    int inizio;
    int fine;
} att;
int durata(att a){       //calcola la durata di un attivita'
   return  a.fine - a.inizio;
}
int checkcompatibilita(att att1, att att2){       //funzione che prende due attività e controlla che siano compatibili
    if(att1.inizio < att2.inizio && att1.fine <= att2.inizio) return 1;
    else return 0;
}
void LISprint(att *v, int *P, int i){
    if(P[i] == -1){
        printf("inizio: %d  fine: %d\n", v[i].inizio, v[i].fine);
        return;
    }
    LISprint(v, P, P[i]);
    printf("inizio: %d  fine: %d\n", v[i].inizio, v[i].fine);
}
void solveDP(att *v, int n){
    int i, j, ris = 1, last = 1, *L, *P;
    L = malloc(n * sizeof(int));
    P = malloc(n * sizeof(int));

    for(i=0; i<n; i++){
        L[i] = 0;
        P[i] = -1;
        for(j=0; j<i; j++)
            if(checkcompatibilita(v[j], v[i]) && L[i] < L[j] + durata(v[j])){
                L[i] += durata(v[j]);
                P[i] = j;
            }
        if(ris < L[i]){
            ris = L[i];
            last = i;
        }
    }
    printf("Sequence: \n");
    LISprint(v, P, last);
    printf("Length: %d", ris);
    free(L);
    free(P);
}

int main() {
    setbuf(stdout, NULL);
    int n_att, max_d = 0, tmp = 0; //durata max e variabile temporanea per la durata max
    att *v;
    FILE *fp = fopen("att2.txt", "r");
    fscanf(fp, "%d", &n_att);

    v = malloc(n_att * sizeof(att));
    for(size_t i=0; i<n_att; i++)
        fscanf(fp, "%d %d", &v[i].inizio, &v[i].fine);
    fclose(fp);

    solveDP(v, n_att);
    free(v);
    return 0;
}
