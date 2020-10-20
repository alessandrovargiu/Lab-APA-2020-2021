#include <stdio.h>
int gcd(int a, int b);
int main() {
    setbuf(stdout, NULL);

    int a, b;
    int mcd;
    printf("Inserisci due interi positivi a e b (a>b) : ");
    scanf("%d %d", &a, &b);

    mcd = gcd(a, b);
    printf("Massimo comune divisore di %d e %d : %d", a, b, mcd);
    return 0;
}
int gcd(int a, int b){
    int tmp;

    if(a<b) {           //il calcolo di mcd si basa su a > b, se non è così scambio i due termini durante la ricorsione
        tmp = a;
        a = b;
        b = tmp;
    }
    //Euclide: l'mcd di a e b%a è lo stesso di a e b
    if(a == b || b == 0) return a;

    if( (a%2 == 0) && (b%2 == 0) ){      //se a,b sono pari
        return 2*gcd(a/2, b/2);
    }
    else if( (a%2 != 0) && (b%2 == 0)) {   //se a è dispari e b pari
        return gcd(a,b/2);
    }
    else if( (a%2 == 0) && (b%2 != 0)) {    //se a è pari e b dispari
        return gcd(a/2, b);
    }
    else if( (a%2 != 0) && (b%2 != 0)) {  //se a,b sono dispari
        return gcd((a - b) / 2, b);
    }
    else return 1;      //i numeri sono primi
}
