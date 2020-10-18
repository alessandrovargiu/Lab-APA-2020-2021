#include <stdio.h>
#include <string.h>
#define max_cod 30
#define max_str 200
typedef struct {
    char word[max_cod];
    char codice[10];
} codifica ;
int main() {
    FILE *fp1, *fp2, *fp3;
    int n_cod, flag=0;
    char str[max_cod], riga[200];
    codifica c[max_cod];
    size_t j=0, k=0, m=0;
    
    fp2 = fopen("dizionario.txt", "r");
    fscanf(fp2, "%d", &n_cod);
    for(int i=0; i<n_cod; i++){
        fscanf(fp2, "%s %s", c[i].codice, c[i].word);               //scan delle parole del dizionario, le salvo in un vettore di struct
    }
    fclose(fp2);
    fp1 = fopen("sorgente.txt", "r");
    fp3 = fopen("ricodificato.txt", "w");

    while(fgets(riga, 201, fp1) != NULL) {      //procedo riga per riga
        j=0;
        while(j<strlen(riga)) {                 //e carattere per carattere nei cicli interni
            flag = 0;
            for (int i = 0; i < n_cod && flag == 0; i++) {
                if(riga[j] == c[i].word[0]){        // possibile sostituzione (comparo con la prima lettera di una parola del dizionario)
                    k=1;
                    while(k<strlen(c[i].word)) {            //esamino le k lettere successive 
                        if(riga[j + k] == c[i].word[k]) k++;
                        else break;
                    }
                    if(k == strlen(c[i].word)) {    //codifica confermata
                        fprintf(fp3, "%s", c[i].codice);
                        flag = 1;
                        j+=k;           //aggiorno la posizione nella riga originale
                    }
                }
            }
            if(flag == 0) {
                fprintf(fp3, "%c", riga[j]);   //stampa il carattere originale
                j++;
            }
        }
    }
    fclose(fp1);
    fclose(fp3);
    return 0;
}
