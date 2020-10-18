#include <stdio.h>
#define MAX 20
void stampa_sottomatrici(int mat[MAX][MAX], int nr, int nc, int c);
int check_sum(int c, int mat[c][c]);
int main() {
    FILE *fp;
    int nr, nc, i, j, c;
    int mat[MAX][MAX];

    fp = fopen("matrice.txt", "r");

    fscanf(fp,"%d %d ", &nr, &nc);  // salvo dimensioni della matrice
    for(i=0; i<nr; i++){
        for(j=0;j<nc;j++) {
            fscanf(fp,"%d", &mat[i][j]);    // salvo la matrice
        }
    }
    fclose(fp);

    do {
        printf("Inserisci un valore compreso tra 1 e 20 (0 per terminare) :");
        scanf("%d", &c);
        stampa_sottomatrici(mat, nr, nc, c);
    }
    while(c>1 && c<=20);

    return 0;
}
void stampa_sottomatrici(int mat[MAX][MAX], int nr, int nc, int c) {
    int s_mat[c][c], i, j, k, m = 0;
    int sum = 0;
    int mat3[c][c];

    for (i = 0; i + c <= nr; i++) {
        for (j = 0; j + c <= nc; j++) {
            for (k = 0; k < c; k++) {
                for (m = 0; m < c; m++) {
                    s_mat[k][m] = mat[i + k][j + m];
                    printf("%d  ", mat[i + k][j + m]);
                }
                printf("\n");
            }
            printf("\n");
            if(check_sum(c, s_mat) > sum) {
                for(int q=0; q<c; q++){
                    for(int p=0; p<c; p++){
                        mat3[q][p] = s_mat[q][p];
                    }
                }
            }
        }
    }
    printf("La matrice con la somma piu' alta dei suoi elementi e':  \n");
    for(int q=0; q<c; q++){
        for(int p=0; p<c; p++){
            printf("%d  ", mat3[q][p]);
        }
        printf("\n");
    }
    printf("\n");
}
int check_sum(int c, int mat[c][c]){
    int sum=0;
    for(int i=0; i<c; i++){
        for(int j=0; j<c; j++){
            sum+=mat[i][j];
        }
    }
    return sum;
}
