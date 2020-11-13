#include <stdio.h>
#include <stdlib.h>
int **malloc2dR(FILE *fp, int *nr, int *nc){
    int **mat;
    mat = malloc(*nr * sizeof(int *));  //vettore di puntatori
    for(size_t i=0; i<*nr; i++){
        mat[i] = malloc(*nc * sizeof(int));
        for (size_t j = 0; j < *nc ; j++) {
            fscanf(fp, "%d", &mat[i][j]);       //riempio la matrice
        }
    }
    return mat;
}
void separa(int **mat, int nr, int nc, int **neri, int **bianchi){  //sto allocando dinamicamente dentro la funzione quindi
                                                                    //devo passare alla funzione un puntatore a puntatore
    *neri = (int *) malloc((nr * nc / 2) + 1 * sizeof(int));
    *bianchi = (int *) malloc(nr*nc/2 * sizeof(int));
    int n=0, b=0, m=1;

    for(size_t i=0; i<nr; i++){
        for (size_t j=0; j<nc; j++) {
            if( m % 2 != 0) {    //se l'indice corrente è dispari prendo un nero
                (*neri)[n] = mat[i][j];
                n++;
            }
            else {                   //senno' prendo un bianco
                (*bianchi)[b] = mat[i][j];
                b++;
            }
            m++;
        }
    }
}
int main() {
    setbuf(stdout, NULL);
    int **mat, *neri, *bianchi;
    int nr, nc, tot;
    FILE *fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);    //leggo le dimensioni della matrice
    tot = nr*nc;

    mat = malloc2dR(fp, &nr, &nc);  //allocazione della matrice
    fclose(fp);

    separa(mat, nr, nc, &neri, &bianchi);  //separazione di elementi bianchi da quelli neri
    //stampa dei vettori richiesti
    printf("caselle nere: ");
    if(tot%2 == 0) {                                    //se il numero di caselle della matrice è pari gli elementi neri sono in numero pari
        for (size_t i = 0; i < (nr * nc / 2); i++)
            printf("%d ", neri[i]);
    }
    else {                                              //se è dispari sono in numero dispari
        for(size_t i=0; i< (nr*nc)/2 + 1; i++)
            printf("%d ", neri[i]);
    }
    printf("\ncaselle bianche: ");
    for(size_t i=0; i<(nr*nc/2); i++)
        printf("%d ", bianchi[i]);

    //deallocazione
    free(neri);
    free(bianchi);
    for(size_t i=0; i<nr; i++)
        free(mat[i]);
    free(mat);
    return 0;
}
