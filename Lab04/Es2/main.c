#include <stdio.h>
#define N 7
int majorityR(int *v, int l, int r);
int majority(int *v);
int main() {
    setbuf(stdout, NULL);
    int v[N];

    printf("Inserisci %d numeri: ", N);
    for(size_t i=0; i<N; i++)
        scanf("%d", &v[i]);
    printf("Elemento maggioritario (-1 se non esiste) : %d", majority(v));
    return 0;
}
int majority(int *v) {      // wrapper
    int l=0, r=N-1;
    return majorityR(v,l,r);
}
int majorityR(int *v, int l, int r){   // O(nlogn)
    int m=(l+r)/2;
    int sx, dx;     //elementi maggioritari del vettore sx e di quello dx
    int cntsx=0, cntdx=0;   //contatori per l'occorrenza di sx o dx

    if(l == r) return v[l];         //foglia dell'albero di ricorsione di dimensione 1
    if(r-l == 1){                   //foglia di dimensione 2
        if(v[r] == v[l]) return v[l];
        return -1;
    }
    //parti sinistra e destra dell'albero di ricorsione
    sx = majorityR(v, l, m);
    dx = majorityR(v, m+1, r);
    //conto le occorrenze di sx e dx
    for(size_t i=l; i<=r; i++){
        if(v[i] == sx)
            cntsx++;
        if(v[i] == dx)
            cntdx++;
    }
    if(cntsx >= m && cntsx > cntdx) return sx;
    if(cntdx >= m) return dx;
    else return -1;             //non esiste un elemento maggioritario

}
