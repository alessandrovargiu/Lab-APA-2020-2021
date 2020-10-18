#include <stdio.h>
#include <string.h>
#define l_nomefile 20
#define maxdim 30
void ruotamatrice(int mat[][maxdim], int nr, int nc,  int indice, int pos, char selettore[], char direzione[]);
void ruota_opt(int v[maxdim], int N, int P, int dir);
int main() {
    setbuf(stdout, NULL);

    FILE *fp;
    char nomefile[l_nomefile];
    int nr, nc, mat[maxdim][maxdim], indice, pos;
    char str[100];
    char selettore[10], direzione[10];
    /* printf("Inserire il nome del file (max 20 caratteri): ");
    scanf("%s", nomefile);
    if(strlen(nomefile) > 20) {
        printf("Nome file troppo lungo. ");
        return -1;
    }                   */
    fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d\n", &nr, &nc);
    for(size_t i=0; i<nr; i++) {
        for(size_t j=0; j<nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    printf("\nInserisci (max 100 caratteri) <selettore> <indice> <direzione> <posizioni> : ");
    while (1) {
        scanf("%s", selettore);
        if (strstr(selettore, "fine")) return (0);
        else {
            scanf(" %d %s %d", &indice, direzione, &pos);
            ruotamatrice(mat, nr, nc, indice, pos, selettore, direzione);
            for(int i=0; i<nr; i++) {
                for(int j=0; j<nc; j++) {
                    printf("%d ", mat[i][j]);
                }
                printf("\n");
            }
        }
    }
}
void ruotamatrice(int mat[][maxdim], int nr, int nc, int indice, int pos, char selettore[], char direzione[]){

    int tmp[maxdim], dir;

    if(!strcmp(direzione, "destra") || !strcmp(direzione, "giu")) dir = 1;
    else dir = -1;

    if(!strcmp(selettore, "riga")){
        for(int i=0; i<nc; i++)
            tmp[i] = mat[indice-1][i];
        ruota_opt(tmp,nc,pos,dir);
        for(int i=0; i<nc; i++)
            mat[indice-1][i] = tmp[i];        //il vettore ruotato viene di nuovo inserito
    }
    else if(!strcmp(selettore, "colonna")){
        for(int i=0; i<nr; i++)
            tmp[i] = mat[i][indice-1];
        ruota_opt(tmp, nr, pos, dir);
        for(int i=0; i<nr; i++)
            mat[i][indice-1] = tmp[i];
    }

}
void ruota_opt(int v[maxdim], int N, int P, int dir) {
    int tmpv[maxdim], i;

    if(dir == 1) P=N-P;    // P spostamenti a DX = N-P spostamenti a SX
    for (i=0; i<P; i++) {
        tmpv[i] = v[i];
    }
    /* sposta di P posizioni a sinistra */
    for (i=0; i<N-P; i++) {
        v[i] = v[i+P];
    }
    /* ricopia a partire da N-P+i  l'intervallo salvato nel vettore temporaneo */
    for (i=0; i<P; i++) {
        v[N-P+i] = tmpv[i];
    }
}
