#include <stdio.h>
#define N 10
int main() {

    int v[N] = {0}, v2[N] = {0};
    int i=0,j=0, max=0;

    printf("Inserisci il vettore: ");
    for(i=0; i<N; i++) scanf("%d", &v[i]) ;

    i=0;
    while (i<=N) {          //trovo la dimensione del sottovettore di lunghezza massima
        if(v[i] == 0) {
            if(j>max) max=j;
            j=-1;
        }
        i++;
        j++;
    }
    if(j>max) max=j;        //nel caso in cui l'ultimo elemento sia non nullo il ciclo non aggiorna il max

    i=0;
    j=0;
    while(i<=N) {
        if(v[i] == 0) {
            i++;
            j=0;
            continue;
        }
        v2[j]=v[i];         //salvo il possibile sottovettore max
        if(j==max-1) {          //se j raggiunge il max ho trovato il sottovettore da stampare
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
