#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_l 255       //max lunghezza titolo canzone
typedef struct {
    char **scelte;
    int num_scelte; //dim del vettore scelte
} Livello;

int princ_molt(int pos, Livello *val, char **sol, int n, int count){
    int i;

    if (pos>=n){        //terminazione
        printf("Playlist n.%d \n", count);
        for(i=0;i<n;i++)
            printf("%s\n ", sol[i]);   //stampa soluzione
        printf("\n");
        return count+1;
    }
    for(i=0; i<val[pos].num_scelte; i++){
        strcpy(sol[pos],val[pos].scelte[i]);        //faccio una scelta
        count = princ_molt(pos+1, val, sol, n, count);  //prossima scelta
    }
    return count;
}
void generaplaylist(Livello *val, int n_amici){
    int count=0;
    char **sol;
    sol = (char **) malloc(n_amici * sizeof(char *));
    for(size_t i=0; i<n_amici; i++)
        sol[i] = (char *) malloc(max_l * sizeof(char));
    //generato il vettore soluzione, ora procedo all'esplorazione dello spazio
    printf("Numero playlist: %d \n",princ_molt(0, val, sol, n_amici, count));

    for(size_t i=0; i<n_amici; i++)
        free(sol[i]);
}
int main() {
    setbuf(stdout, NULL);
    FILE *fp;
    int n_amici;
    Livello *val;
    fp = fopen("brani.txt", "r");
    fscanf(fp, "%d", &n_amici);

    val =  malloc(n_amici * sizeof(Livello));

    for(size_t i=0; i<n_amici; i++){
        fscanf(fp, "%d", &val[i].num_scelte);      //numero di canzoni scelte dall' i-esimo amico
        val[i].scelte =  malloc(val[i].num_scelte * sizeof(char *));      //vettore di puntatori a char
        for(size_t j=0; j<val[i].num_scelte; j++) {
            val[i].scelte[j] =  malloc(max_l * sizeof(char));
            fscanf(fp, "%s", val[i].scelte[j]);   //salvo la canzone da file
        }
    }
    fclose(fp);
    generaplaylist(val, n_amici);

    //tutta sta merda sarebbe meglio che la facesse una funzione apposita ma oggi son particolarmente pigro
    for(size_t i=0; i<n_amici; i++){
        for(size_t j=0; j<val[i].num_scelte; j++){
            free(val[i].scelte[j]);
        }
        free(val[i].scelte);
    }
    free(val);
    return 0;
}
