#include <stdio.h>
#define N 20
int main() {
    setbuf(stdout, NULL);
    int mat[N][N], nr, nc;
    int vet[N] = {0};         //segno il punteggio max per ogni giornata
    FILE *fp;
    fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);

    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            fscanf(fp,"%d", &mat[i][j]);
            if(mat[i][j] > vet[j]) vet[j] = mat[i][j];
        }
    }

    printf("Squadre capolista delle giornate: \n");
    for(int i=0; i<nc; i++) {
        printf("Giornata %d : ", i+1);
        for(int j=0; j<nr; j++){
            if(mat[j][i] == vet[i]) {
                printf("%d ", j+1);
            }
        }
        printf("\n");
    }
    return 0;
}
