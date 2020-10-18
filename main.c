#include <stdio.h>
#define N 10
int main() {

    int v[N] = {0}, v2[N] = {0};
    int i=0,j=0, max=0;

    printf("Inserisci il vettore: ");
    for(i=0; i<N; i++) scanf("%d", &v[i]) ;

    i=0;
    while (i<=N) {
        if(v[i] == 0) {
            if(j>max) max=j;
            j=-1;
        }
        i++;
        j++;
    }
    if(j>max) max=j;

    i=0;
    j=0;
    while(i<=N) {
        if(v[i] == 0) {
            i++;
            j=0;
            continue;
        }
        v2[j]=v[i];
        if(j==max-1) {
            for(int k=0; k<max; k++) {
                printf("%d ",v2[k]);
            }
            j=-1;
        }
        j++;
        i++;
    }


    return 0;
}
