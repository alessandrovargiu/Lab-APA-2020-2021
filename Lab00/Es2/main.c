#include <stdio.h>
#include <string.h>
#define M 20    //max caratteri per parola
int conta(char S[M], int n, int l);
int main() {

    FILE *fp;
    int N, n=0;      // N - numero parole nel file
    int l, tot=0;     // tot - numero totale sottostringhe
    char nomefile[200] = "testo.txt";
    char word[M];

    printf("Inserisci lunghezza delle sottostringhe: ");
    scanf("%d", &l);
    fp = fopen(nomefile, "r");

    if(fscanf(fp, "%d", &N) == 0) {
        printf("Errore durante la lettura del file. ");
        return -1;
    }
    for(int i=0; i<N; i++) {
         fscanf(fp, "%s", word);
         tot += conta(word, n, l);
    }
    fclose(fp);

    return tot;
}
int conta(char S[M], int n, int l){
    int cnt = 0;

    for(int i=0; i<strlen(S); i++) {
        cnt = 0;
        for(int j=i; j<i+l && j<strlen(S); j++) {
            if(S[j] == 'a' || S[j] == 'e' || S[j] == 'i' || S[j] == 'o' || S[j] == 'u'
            || S[j] == 'A' || S[j] == 'E' || S[j] == 'I' || S[j] == 'O' ||S[j] == 'U') {
                cnt++;
            }
        }
        if(cnt == 2) n++;
    }
    return n;
}
