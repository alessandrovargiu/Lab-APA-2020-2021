#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct pietre{      //contenitore delle pietre con relativo valore
    char tipo;          //iniziale del nome della pietra
    int value;
    int amount;
} Pietre;

int pruning(char *sol, int pos, char tipo, int max_rip){
    int count=0;
    if(pos != 0) {
        if (pos >= max_rip) {        //non ha senso considerare le ripetizioni di una pietra se non ho ancora raggiunto max_rip posizioni
            for (size_t j = 0; j < max_rip; j++) {
                if (sol[pos - j] == sol[pos - 1])      //Se la pietra è ripetuta
                    count++;
                else break;
            }
            if (count >= max_rip && sol[pos] == tipo)          //se la pietra è ripetuta troppe volte non posso prenderla di nuovo
                return 0;
        }
        switch (sol[pos-1]) {
            case 'z':
                if (tipo != 'z' && tipo != 'r')  //se non rispetto le condizioni richieste sulla pietra precedente
                    return 0;                   //allora non posso fare questa scelta
                return 1;
            case 's':
                if (tipo != 's' && tipo != 't')
                    return 0;
                return 1;
            case 'r':
                if (tipo != 's' && tipo != 't')
                    return 0;
                return 1;
            case 't':
                if (tipo != 'z' && tipo != 'r')
                    return 0;
                return 1;
        }
    }
    return 1;       //se sono alla prima scelta non devo fare controlli
}
int disp_ripet(int pos, Pietre *p, char *sol, char *solmax, int *value, int *lmax, int maxrip, int n, int k, int count) {
    int i, n_r = 0, n_s = 0, n_z = 0, n_t = 0;
    int current_value = 0;
    if (pos >= k) {
        for (i=0; i<k; i++) {
            switch(sol[i]){
                case 'z':
                    n_z++;
                    break;
                case 's':
                    n_s++;
                    break;
                case 'r':
                    n_r++;
                    break;
                case 't':
                    n_t++;
                    break;
            }
        }
        if(n_z <= n_s) {
            current_value = p[0].value * n_z + p[1].value * n_s + p[2].value * n_r + p[3].value * n_t;
            if (current_value > *value) {
                *value = current_value;      //valore max della soluzione aggiornato
                *lmax = n_r + n_s + n_z + n_t;
                strcpy(solmax, sol);        //nuova soluzione max
            }
        }
        return count+1;
    }
    for (i = 0; i < n; i++) {
        if (p[i].amount > 0 && pruning(sol, pos, p[i].tipo, maxrip)) {
            sol[pos] = p[i].tipo;
            p[i].amount--;
            count = disp_ripet(pos + 1, p, sol, solmax, value, lmax,  maxrip, n, k, count);
            p[i].amount++;
        }
    }
    return count;
}
void raccogli_pietre(FILE *fp){
    Pietre p[4];
    p[0].tipo = 'z'; p[1].tipo = 's'; p[2].tipo = 'r'; p[3].tipo = 't';
    char *sol, *solmax;
    int value = 0, lmax = 0;
    int maxrip, count = 0, length;
    fscanf(fp, "%d %d %d %d %d %d %d %d %d", &p[0].amount, &p[1].amount, &p[2].amount, &p[3].amount, &p[0].value, &p[1].value, &p[2].value, &p[3].value, &maxrip);
    length = p[0].amount + p[1].amount + p[2].amount + p[3].amount;
    sol = malloc(length+1 * sizeof(char));
    solmax = malloc(length+1 * sizeof(char));

    for(size_t i=1; i < length; i++) {       //powerset con disp. ripetute
        disp_ripet(0, p, sol, solmax, &value, &lmax, maxrip, 4, i, count);
    }
    printf("\nLa collana di valore max %d e' (lunghezza %d): \n", value, lmax);
    for(size_t i=0; i<lmax; i++){
        printf("-%c", solmax[i]);
    }

    free(sol);
    free(solmax);
}
int main() {
    setbuf(stdout, NULL);
    int i;
    int n_test;
    FILE *fp = fopen("test_set.txt", "r");
    fscanf(fp, "%d", &n_test);
    for(i=0; i<n_test; i++)
        raccogli_pietre(fp);
    fclose(fp);
    return 0;
}
