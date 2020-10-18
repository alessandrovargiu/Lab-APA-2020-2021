#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define word_l 25
void row_scan(char seq[]);
void strToLower(char s[]);
int main() {
    setbuf(stdout, NULL);
    FILE *fps;
    int ns;
    char sequenza[6];
    fps = fopen("sequenze.txt", "r");
    fscanf(fps, "%d", &ns);
    for(size_t i=0; i<ns; i++){
        fscanf(fps, "%s", sequenza);
        printf("\nLa sequenza %s e' contenuta in ", sequenza);
        row_scan(sequenza);
    }
    fclose(fps);
    return 0;
}
void row_scan(char seq[]) {
    FILE *fpt = fopen("testo.txt", "r");
    char row[201], word[word_l], word_originale[word_l];
    int i=0,j=1,k=0;         //j conta la posizione in cui sono nel testo
    int p=0;
    while(fgets(row, 200, fpt) != NULL) {
        i=0;
        while(row[i] != '\0'){
            if(isalnum(row[i])) {           //if carattere alfanum --> salvo nella word e aumento k
                word[k] = row[i];
                k++;
                p = 0;
            }
            else {
                if(p == 0) {
                    if (isspace(row[i]) || ispunct(row[i])) {           //se trovo uno spazio cerco la sequenza nella parola salvata
                        if(ispunct(row[i])) p = 1;
                        j++;                     //posizione+1
                        word[k] = '\0';        //la parola termina qui
                        k = 0;                     //lunghezza di una parola resettata per la successiva
                        strcpy(word_originale, word);           //copio la stringa in un altra per mantenere i caps nella stampa
                        strToLower(word);
                        strToLower(seq);
                        if (strstr(word, seq)) {
                            printf("%s (posizione %d), ", word_originale, j - 1);
                        }
                    }
                } else if(isspace(row[i])){
                    //ignoro lo spazio dopo un carattere di punteggiatura e vado avanti
                    p = 0;
            }
        }
        i++;
    }
}
    rewind(fpt);
}
void strToLower(char s[]){
    for(int i=0; s[i]!='\0'; i++)
        s[i] = tolower(s[i]);
}
