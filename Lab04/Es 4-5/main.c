#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxstr 30
typedef enum command {
    c_stampa, o_data, o_tratta, o_partenza, o_arrivo, r_partenza, c_fine
} command;
typedef enum tipo_ord {         //costante per selezionare il modo in cui confrontare gli elementi nel merge
    data, tratta, partenza, arrivo
} tipo_ord;
typedef struct tratta {
    char cod_t[maxstr], p[maxstr], a[maxstr], data[maxstr], ora_p[maxstr], ora_a[maxstr];
    int ritardo;
} Tratta;
Tratta *ordinamenti[4];             //vettore di puntatori al tipo Tratta con cui gestisco contemporaneamente
                                    // gli ordinamenti
int checkdataora(char data1[], char data2[], char ora1[], char ora2[]);
void selezioneDati(command c, Tratta v[], int nr);
void strToLower(char s[]);
command leggiComando();
int ITEMlt_eq(Tratta a, Tratta b, tipo_ord ordine){
    switch(ordine){
        case 0:
            return checkdataora(a.data,b.data,a.ora_p,b.ora_p);
        case 1:
            if(strcmp(a.cod_t, b.cod_t) <= 0) return 1;
            else return 0;
        case 2:
            if(strcmp(a.p,b.p) <= 0) return 1;
            else return 0;
        case 3:
            if(strcmp(a.a,b.a) <= 0) return 1;
            else return 0;
    }
}
void Merge(Tratta *A, Tratta *B, int l, int q, int r, tipo_ord ordine) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (ITEMlt_eq(A[i],A[j],ordine))
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
}
void MergeSortR(Tratta *A, Tratta *B, int l, int r, tipo_ord ordine) {
    int q;
    if (r <= l)
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q, ordine);
    MergeSortR(A, B, q+1, r, ordine);
    Merge(A, B, l, q, r, ordine);
}
void MergeSort(Tratta *A, int N, tipo_ord ordine) {
    int l=0, r=N-1;
    Tratta *B = (Tratta *)malloc(N*sizeof(Tratta));
    if (B == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    MergeSortR(A, B, l, r, ordine);         // O(nlogn)
    free(B);
}
void ordina(Tratta v[], int nr){          //funzione wrapper chiamata all'inizio del programma per creare tutti gli ordinamenti richiesti
    //alloca i vettori necessari per i vari ordinamenti
    for(size_t i=0; i<4; i++) {
        ordinamenti[i] = malloc(nr * sizeof(Tratta));
        memcpy(ordinamenti[i], v, nr * sizeof(Tratta));
    }
    // creo i vari ordinamenti
    MergeSort(ordinamenti[0], nr, 0);
    MergeSort(ordinamenti[1], nr, 1);
    MergeSort(ordinamenti[2], nr, 2);
    MergeSort(ordinamenti[3], nr, 3);

}
void BinSearch(Tratta v[], int l, int r, char k[]) {   // O(log n)
    int i=0, m=0;
    int len = r;    //salvo la lunghezza totale del vettore, da usare nella ricerca di piu' elementi con la stessa chiave (vedi fine blocco)
    while(l<=r) {
        m = (l+r)/2;
        if(strncmp(v[m].p, k, strlen(k)) == 0) {
            printf("Tratta: %s %s %s %s %s %s %d\n", v[m].cod_t, v[m].p, v[m].a, v[m].data, v[m].ora_p, v[m].ora_a, v[m].ritardo);
            break;
        }
        if(strcmp(v[m].p, k) < 0)
            l = m+1;
        else
            r = m-1;
    }
    if(l>r) printf("Tratta non trovata.\n");
    else {
        i=m+1;
        while(i<len && (strncmp(v[i].p, k, strlen(k))) == 0){   //stampa finchè non trovo elementi che non corrispondono alla chiave
            printf("Tratta: %s %s %s %s %s %s %d\n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
            i++;
        }
        i=m-1;
        while(i>=0 && (strncmp(v[i].p, k, strlen(k))) == 0){
            printf("Tratta: %s %s %s %s %s %s %d\n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
            i--;
        }
    }
}
int main() {
    setbuf(stdout, NULL);
    FILE *fp;
    int nr;         //righe del file
    char nomefile[10] = "log.txt";
    Tratta *v;
    command c;

    fp=fopen(nomefile, "r");
    fscanf(fp, "%d", &nr);
    v = malloc (nr * sizeof(Tratta));   //vettore dinamico di elem. Tratta
    for(int i=0; i<nr; i++){    //log inserito in opportuna struttura dati
        fscanf(fp, "%s %s %s %s %s %s %d", v[i].cod_t, v[i].p, v[i].a, v[i].data,v[i].ora_p, v[i].ora_a, &v[i].ritardo);
    }
    fclose(fp);
    ordina(v, nr);               //creo tutti gli ordinamenti possibili
    while(1){
        c = leggiComando();
        if(c == c_fine) return 0;
        else selezioneDati(c, v, nr);
    }

}
void stampalog(Tratta v[], int nr){
    int s;

    printf("0 per stampa su video, 1 per stampa su file\n");
    scanf("%d", &s);
    if(s == 0){
        for(size_t i=0; i<nr; i++){
            printf("%s %s %s %s %s %s %d\n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
        }
    }
    else if(s == 1){
        FILE *fp;
        fp = fopen("log2.txt", "w");
        for(size_t i=0; i<nr; i++) fprintf(fp, "%s %s %s %s %s %s %d\n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
        fclose(fp);
    }
    else printf("Scelta errata.\n");
}
void selezioneDati(command c, Tratta v[], int nr){
    switch(c){
        char staz[10];
        case c_stampa:
            stampalog(v, nr);
            break;
        case o_data:
            stampalog(ordinamenti[0], nr);
            break;
        case o_tratta:
            stampalog(ordinamenti[1], nr);
            break;
        case o_partenza:
            stampalog(ordinamenti[2], nr);
            break;
        case o_arrivo:
            stampalog(ordinamenti[3], nr);
            break;
        case r_partenza:
            printf("Inserisci una stazione di partenza: \n");
            scanf("%s", staz);
            BinSearch(ordinamenti[2], 0, nr, staz);  //avendo il vettore ordinato per staz. di partenza opto per la binsearch
            break;
        default: printf("comando errato");
    }
}
int checkdataora(char data1[], char data2[], char ora1[], char ora2[]) {
    //ritorno 1 se data e ora sono uguali o se la prima e minore della seconda
    int gg1, gg2, mm1, mm2, aa1, aa2;
    int hh1, hh2, min1, min2, ss1, ss2;
    sscanf(data1, "%d/%d/%d", &aa1, &mm1, &gg1);
    sscanf(data2, "%d/%d/%d", &aa2, &mm2, &gg2);
    sscanf(ora1, "%d/%d/%d", &hh1, &min1, &ss1);
    sscanf(ora2, "%d/%d/%d", &hh2, &min2, &ss2);

    if(gg1==gg2 && mm1==mm2 && aa1==aa2) {
        if (hh1 == hh2 && min1 == min2 && ss1 == ss2)
            return 1;   //data e ora sono uguali --> i due elementi confrontati nel merge sono uguali
        else if(hh1==hh2){
                if(min1==min2){
                    if(ss1<ss2) {
                        return 1;
                    }
                }
                else if(min1<min2) return 1;
        }
        else if(hh1<hh2) return 1;
    }
    else if(aa1==aa2) {
            if (mm1 == mm2) {
                if (gg1 < gg2) {
                    return 1;
                }
            }
            else if(mm1<mm2) return 1;
        }
    else if(aa1<aa2) return 1;
    return 0;        //se uno qualsiasi dei casi precedenti non è soddisfatto allora il primo elemento è maggiore del secondo nel merge
}
command leggiComando(){
    command c;
    char *tabella[c_fine+1] = {
            "stampa", "data", "tratta", "partenza", "arrivo", "ricerca", "fine"
    };
    char cmd[maxstr];

    printf("Comandi:\nstampa --> stampa contenuti del log originale su schermo\nOrdinamenti:\ndata | tratta | partenza | arrivo\n");
    printf("'ricerca' per cercare una tratta per stazione di partenza\n");
    printf("Premi 0 per terminare \n");
    scanf("%s", cmd);
    strToLower(cmd);
    c = c_stampa;
    while(c<c_fine && strcmp(cmd, tabella[c])!=0)
        c++;
    return c;
}
void strToLower(char s[]){
    for(int i=0; s[i]!='\0'; i++)
        s[i] = tolower(s[i]);
}
