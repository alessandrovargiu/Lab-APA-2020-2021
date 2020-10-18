#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define maxstr 30
typedef enum command {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
} command;
typedef struct tratta {
    char cod_t[maxstr], p[maxstr], a[maxstr], data[maxstr], ora_p[maxstr], ora_a[maxstr];
    int ritardo;
} Tratta;
void partenza_data(Tratta v[], int nr);
int checkdata(char data1[], char data2[], char data[]);
void selezioneDati(command c, Tratta v[], int nr);
void strToLower(char s[]);
command leggiComando();
int main() {
    setbuf(stdout, NULL);
    FILE *fp;
    int nr;         //righe del file
    char nomefile[10] = "log.txt";
    Tratta v[1000];
    command c;
    fp=fopen(nomefile, "r");
    fscanf(fp, "%d", &nr);

    for(int i=0; i<nr; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", v[i].cod_t, v[i].p, v[i].a, v[i].data,v[i].ora_p, v[i].ora_a, &v[i].ritardo);;
    }
    fclose(fp);
    while(1){
        c = leggiComando();
        if(c == r_fine) return 0;
        else selezioneDati(c, v, nr);
    }

}
void partenza_data(Tratta v[], int nr){
    char data1[11], data2[11];
    printf("Inserisci un intervallo di date (yyyy/mm/gg): \n data1: ");
    scanf("%s", data1);
    printf("\ndata2: ");
    scanf("%s", data2);
    printf("Corse partite tra %s e %s \n", data1, data2);
    for(size_t i=0; i<nr; i++){
        if(checkdata(data1, data2, v[i].data))
            printf("%s %s %s %s %s %s %d \n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
    }
}
void check_partenza(Tratta v[], int nr){
    char p[maxstr];
    printf("Inserisci una fermata: ");
    scanf("%s", p);

    for(size_t i=0; i<nr; i++){
        if(!strcmp(v[i].p, p)) {
            printf("%s %s %s %s %s %s %d \n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
        }
    }
}
void check_capolinea(Tratta v[], int nr){
    char c[maxstr];
    printf("Inserisci una fermata: ");
    scanf("%s", c);
    printf("Corse che fanno capolinea alla fermata %s: \n", c);
    for(size_t i=0; i<nr; i++){
        if(!strcmp(v[i].a, c)) {
            printf("%s %s %s %s %s %s %d \n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
        }
    }
}
void check_ritardo(Tratta v[], int nr){
    char data1[11], data2[11];
    printf("Inserisci un intervallo di date (gg/mm/yyyy): \n data1: ");
    scanf("%s", data1);
    printf("\ndata2: ");
    scanf("%s", data2);
    for(size_t i=0; i<nr; i++){
        if(checkdata(data1, data2, v[i].data) && v[i].ritardo>0){
            printf("%s %s %s %s %s %s %d \n", v[i].cod_t, v[i].p, v[i].a, v[i].data, v[i].ora_p, v[i].ora_a, v[i].ritardo);
        }
    }
}
void check_ritardotot(Tratta v[], int nr){
    char codt[maxstr];
    int ritardo = 0;
    printf("Inserisci il codice di una tratta: ");
    scanf("%s", codt);
    for(size_t i=0; i<nr; i++){
        if(!strcmp(v[i].cod_t, codt))
            ritardo+=v[i].ritardo;
    }
    printf("\n Ritardo totale accumulato dalla tratta %s : %d \n", codt, ritardo);
}
void selezioneDati(command c, Tratta v[], int nr){
    switch(c){
        case r_date:
            partenza_data(v, nr);
            break;
        case r_partenza:
            check_partenza(v, nr);
            break;
        case r_capolinea:
            check_capolinea(v, nr);
            break;
        case r_ritardo:
            check_ritardo(v, nr);
            break;
        case r_ritardo_tot:
            check_ritardotot(v, nr);
            break;
        default: printf("comando errato");
    }
}
int checkdata(char data1[], char data2[], char data[]) {        //controlla se una data è compresa tra un intervallo dato a priori
    int gg1, gg2, gg, mm1, mm2, mm, aa1, aa2, aa;
    sscanf(data1, "%d/%d/%d", &gg1, &mm1, &aa1);
    sscanf(data2, "%d/%d/%d", &gg2, &mm2, &aa2);
    sscanf(data, "%d/%d/%d", &gg, &mm, &aa);
    if (aa >= aa1 && aa <= aa2) {
        if (mm >= mm1 && mm <= mm2) {
            if (gg >= gg1 && gg <= gg2) {
                return 1;
            }
        }
    }
    return 0;
}
command leggiComando(){
    command c;
    char *tabella[r_fine+1] = {
            "date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"
    };
    char cmd[maxstr];

    printf("Inserisci un comando per creare l'elenco: (date, partenza, capolinea, ritardo, ritardotot, fine\n");
    scanf("%s", cmd);
    strToLower(cmd);
    c = r_date;
    while(c<r_fine && strcmp(cmd, tabella[c])!=0)
        c++;
    return c;
}
void strToLower(char s[]){
    for(int i=0; s[i]!='\0'; i++)
        s[i] = tolower(s[i]);
}
