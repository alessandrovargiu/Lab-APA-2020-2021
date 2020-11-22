#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxl 50

typedef enum command {
    ins_key, ins_file, cod_search, cod_rm, date_rm, print, end
} command;
typedef struct Key {
    char datanascita[11];
} Key;
typedef struct item {
    Key datanascita;
    char codice[maxl],
         nome[maxl],
         cognome[maxl],
         via[maxl],
         citta[maxl];
    int cap;
} ITEM ;
typedef struct node *link;
struct node {
    ITEM val;
    link next;
};

int checkdataora(char data1[], char data2[]) {
    //ritorno 1 se data e ora sono uguali o se la prima e' minore della seconda
    int gg1, gg2, mm1, mm2, aa1, aa2;
    sscanf(data1, "%d/%d/%d", &gg1, &mm1, &aa1);
    sscanf(data2, "%d/%d/%d", &gg2, &mm2, &aa2);


    if(gg1==gg2 && mm1==mm2 && aa1==aa2)
            return 1;   //data e ora sono uguali

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
Key KEYget(ITEM val){
    return val.datanascita;
}
int KEYgreater(Key key1, Key key2){
    return checkdataora(key1.datanascita, key2.datanascita);
}
void ITEMprint(ITEM val){
    printf("%s %s %s %s %s %s %d\n", val.codice, val.nome, val.cognome, val.datanascita.datanascita, val.via, val.citta, val.cap);
}

link newNode(ITEM val, link next){
    link x = malloc(sizeof(*x));    //alloco nodo
    if(x==NULL) return NULL;    //allocazione non riuscita
    //creazione
    x->val = val;
    x->next = next;
    return x;
}
link SortListIns(link h, ITEM val){             // O(n)
    link x, p;
    Key k = KEYget(val);
    if(h==NULL || KEYgreater(KEYget(h->val), k))
        return newNode(val, h);
    for (x=h->next, p=h;  x!=NULL && KEYgreater(k, KEYget(x->val)) ; p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}
ITEM *ListSearch(link h, char *k){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(strcmp(k, x->val.codice) == 0)
            return &x->val;
    }
    return NULL;
}
link listDelKeyR(link x, char *k){      // O(n) funzione ricorsiva
    link t;
    if(x == NULL) return NULL;
    if(strcmp(x->val.codice, k)==0){
        printf("Elemento trovato. Cancellazione eseguita.\n");
        ITEMprint(x->val);
        t = x->next;
        free(x);
        return t;
    }
    x->next = listDelKeyR(x->next, k);
    return x;
}
link SortListDel(link h, Key k1, Key k2){
    link x,p;
    if (h==NULL) return NULL;
    for(x=h, p=NULL; x!=NULL && KEYgreater(k1,KEYget(x->val)) ; p=x, x=x->next){
        if(KEYgreater(KEYget(x->val),k2)){
            if(x==h) {
                h = x->next;
                return x;
            }
            else {
                p->next = x->next;
                return x;
            }
        }
    }
    return NULL;
}

void delete_date(link *head){
    Key date1, date2;
    link p;
    printf("Inserisci due date, verranno eliminati i soggetti con data di nascita compresa tra queste\n");
    scanf("%s %s", date1.datanascita, date2.datanascita);
    while((p = SortListDel(*head, date1, date2)) != NULL){
        printf("Elemento eliminato:\n");
        ITEMprint(p->val);
        printf("\n");
    }
    printf("Ricerca terminata.\n");
}
void delete_code(link *head){
    char code[maxl];
    ITEM *p;
    printf("Inserisci il codice: \n");
    scanf("%s", code);
    listDelKeyR(*head, code);
}
void ricerca_cod(link *head){
    char code[maxl];
    ITEM *p;
    printf("Inserire il codice: \n");
    scanf("%s", code);
    p = ListSearch(*head, code);
    if(p==NULL) printf("Elemento non trovato.\n");
    else {
        printf("Elemento trovato:\n");
        ITEMprint(*p);
    }
}
void printlist(link *head){
    link x;
    for(x=*head; x!=NULL; x=x->next) ITEMprint(x->val);
}
void leggifile(link *head){
    char nomefile[20];
    FILE *fp;
    ITEM *val = malloc(sizeof(ITEM));

    printf("Inserisci il nome del file da leggere: \n");
    scanf("%s", nomefile);
    fp = fopen(nomefile, "r");
    while(fscanf(fp, "%s %s %s %s %s %s %d", val->codice, val->nome, val->cognome, val->datanascita.datanascita, val->via, val->citta, &val->cap) != EOF){
        *head = SortListIns(*head, *val);
    }
    fclose(fp);
}
void ins_keyboard(link *head){
    ITEM *val = malloc(sizeof(ITEM));
    printf("Inserire i seguenti dati : <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
    scanf("%s %s %s %s %s %s %d", val->codice, val->nome, val->cognome, val->datanascita.datanascita, val->via, val->citta, &val->cap);
    *head = SortListIns(*head, *val);
}

command leggiComando(){
    command c;
    char *tabella[end+1] = {
            "ins_key", "ins_file", "cod_search", "cod_rm", "date_rm", "print", "end"
    };
    char cmd[maxl];
    printf("Comandi:\nins_key -> inserimento da tastiera\nins_file -> inserimento da file\ncod_search -> ricerca per codice"
           "\ncod_rm -> cancellazione per codice\ndate_rm -> cancellazione per data\nprint -> stampa lista\nend -> fine programma\n");
    scanf("%s", cmd);
    c = ins_key;
    while(c<end && strcmp(cmd, tabella[c])!=0)
        c++;
    return c;
}
int main() {
    setbuf(stdout, NULL);
    link head = NULL;       //inizializzo una lista vuota

    while(1) {
        command c = leggiComando();
        switch (c) {
            case ins_key:
                ins_keyboard(&head);
                break;
            case ins_file:
                leggifile(&head);
                break;
            case cod_search:
                ricerca_cod(&head);
                break;
            case cod_rm:
                delete_code(&head);
                break;
            case date_rm:
                delete_date(&head);
                break;
            case print:
                printlist(&head);
                break;
            case end:
                return 0;
            default:
                printf("Comando errato.\n");
                break;
        }
    }
}
