#include <stdio.h>
#define maxN 30
void ruota(int v[maxN], int N, int P, int dir);
int main() {
    int N, P, dir, v[maxN];
    int i=0;
    printf("Inserire la lunghezza del vettore: ");
    scanf("%d", &N);

    printf("Inserisci il vettore: ");
    for(i=0; i<N; i++){
        scanf("%d", &v[i]);
    }
    printf("Inserisci P (0 per terminare) e dir (-1 || 1): ");
    scanf("%d %d", &P, &dir);
    if(P==0) return -1;
    ruota(v, N, P, dir);
    for(int i=0; i<N; i++) printf("%d ", v[i]);

    return 0;
}
void ruota(int v[maxN], int N, int P, int dir) {
    int tmp, i, j;

    if (dir == -1){
        for(i=0; i<P; i++){
            tmp= v[N-1];
            for(j=N-1;j>0;j--){
                v[j] = v[j - 1];
            }
            v[0]=tmp;
        }
    }
    else if(dir == 1){
        for(i=0; i<P; i++){
            tmp = v[0];
            for(j=0;j<N-1;j++){
                v[j]=v[j+1];
            }
            v[j] = tmp;
        }
    }
}
