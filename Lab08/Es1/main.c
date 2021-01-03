#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pietre{      //contenitore delle pietre disponibili
    char type;
    int amount;
} Pietre;
int check_amount(size_t i, Pietre *val){
    switch(i){
        case 0:             //zaffiro
            if(val[0].amount > 0)
                return 1;
            else
                return 0;
        case 1:             //rubino
            if(val[1].amount > 0)
                return 1;
            else
                return 0;
        case 2:             //topazio
            if(val[2].amount > 0)
                return 1;
            else
                return 0;
        case 3:             //smeraldo
            if(val[3].amount > 0)
                return 1;
            else
                return 0;
        default:
            break;
    }
}
int pruning(char *sol, int n, size_t i){
    switch(sol[n]){
        case 'z':
            if(i == 0 || i == 1)        //zaffiro o rubino
                return 1;
            else return 0;
        case 'r':
            if(i == 3 || i == 2)        //smeraldo o topazio
                return 1;
            else return 0;
        case 's':
            if(i == 3 || i == 2)        //smeraldo o topazio
                return 1;
            else return 0;
        case 't':
            if(i == 0 || i == 1)        //zaffiro o rubino
                return 1;
            else return 0;
    }
}
// n -> lunghezza collana corrente;  k -> n. tipi di pietre
int disp_ripetute(int pos, Pietre *val, char *sol, char *solmax, int k, int *max, int length){
    int flag = 0;       //setto a 1 quando faccio una scelta, se finisco il for senza aver fatto nessuna scelta vuol dire che sono arrivato alla collana max

    for(size_t i=0; i<k; i++) {      //per ogni tipo di pietra
        if (pos == 0) {       //la prima scelta va sempre bene
            val[i].amount--;
            sol[pos] = val[i].type;
            disp_ripetute(pos + 1, val, sol, solmax, k, max, length);
            val[i].amount++;
        }
        else if(check_amount(i, val) && pruning(sol, pos - 1,i)) {          //se ci sono ancora pietre disponibili ed è possibile fare questa scelta
            flag = 1;
            val[i].amount--;
            sol[pos] = val[i].type;
            disp_ripetute(pos+1, val, sol, solmax, k, max, length);
            val[i].amount++;
        }
    }
    if(flag == 0 && pos != 0){          //terminazione, raggiunto il max per questa configurazione di pietre
        if(pos > *max) {            //trovato nuova collana max
            strcpy(solmax, sol);
            *max = pos;
        }
    }
}
void raccogli_pietre(FILE *fp, int *i){
    Pietre p[4];            // 0 -> zaffiro ; 1 -> rubino ; 2 -> topazio ; 3 -> smeraldo
    p[0].type = 'z';
    p[1].type = 'r';
    p[2].type = 't';
    p[3].type = 's';
    int length=0;      // num. tot di pietre
    char *sol, *solmax;
    int max=0;

    fscanf(fp, "%d %d %d %d", &p[0].amount, &p[1].amount, &p[2].amount, &p[3].amount);

    length = p[0].amount + p[1].amount + p[2].amount + p[3].amount;
    sol = malloc(length+1 * sizeof(char));
    solmax = malloc(length+1 * sizeof(char));

    disp_ripetute(0, p, sol, solmax, 4, &max, length);
    printf("\nLa collana di lunghezza max = %d e' : ", max);
    for(size_t j=0; j<max; j++){
        printf("-%c", solmax[j]);
    }

    free(sol);
    free(solmax);
}
int main() {
    setbuf(stdout, NULL);
    int i;
    int n_test;
    FILE *fp = fopen("easy_test_set.txt", "r");
    fscanf(fp, "%d", &n_test);
    for(i=0; i<n_test; i++)
        raccogli_pietre(fp, &i);
    fclose(fp);
    return 0;
}
