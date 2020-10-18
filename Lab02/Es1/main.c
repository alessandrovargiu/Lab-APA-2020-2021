#include <stdio.h>
#define dim 50
typedef struct regione {
    int x, y;
    int base, altezza, area;
} Regione;
void scan_matrice(int mat[][dim], int nr, int nc);
int base(int mat[][dim], int nc, int i, int j);
int altezza(int mat[][dim], int nr, int i, int j);
void save_region(Regione *reg, int i, int j, int b, int h, int a);
int main() {
    setbuf(stdout, NULL);
    int mat[dim][dim], nr, nc;
    FILE *fp;
    char nomefile[10] = "mappa.txt";

    fp=fopen(nomefile, "r");
    fscanf(fp, "%d %d", &nr, &nc);

    for(int i=0; i<nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    scan_matrice(mat, nr, nc);
    return 0;
}
void scan_matrice(int mat[][dim], int nr, int nc){
    int i,j, bmax=0, hmax=0, amax=0;
    int b, a, h;
    Regione reg[3];
    for(i=0; i<nr; i++){
        for(j=0;j<nc; j++){
            if(mat[i][j]){
                b = base(mat, nc, i, j);
                h = altezza(mat, nr, i, j);
                a = b*h;
                if(b > bmax){
                    save_region(&reg[0],i,j,b,h,a);
                    bmax = b;
                }
                if(h > hmax) {
                    save_region(&reg[1],i,j,b,h,a);
                    hmax = h;
                }
                if(a > amax) {
                    save_region(&reg[2],i,j,b,h,a);
                    amax = a;
                }
            }
        }
    }

    printf("Regione con la base maggiore e_sx:(x,y) : (%d, %d) b = %d h = %d, a = %d\n", reg[0].x, reg[0].y, reg[0].base, reg[0].altezza, reg[0].area);
    printf("Regione con l'altezza maggiore e_sx:(x,y) : (%d, %d) b = %d h = %d, a = %d\n", reg[1].x, reg[1].y, reg[1].base, reg[1].altezza, reg[1].area);
    printf("Regione con l'area maggiore e_sx:(x,y) : (%d, %d) b = %d h = %d, a = %d\n", reg[2].x, reg[2].y, reg[2].base, reg[2].altezza, reg[2].area);
}
int base(int mat[][dim], int nc, int i, int j){
    int b=0;
    while(j<nc && mat[i][j]) {
        j++;
        b++;
    }
    return b;
}
int altezza(int mat[][dim], int nr, int i, int j){
    int h=0;
    while(i<nr && mat[i][j]){
        i++;
        h++;
    }
    return h;
}
void save_region(Regione *reg, int i, int j, int b, int h, int a){
    reg->x = i;
    reg->y = j;
    reg->base = b;
    reg->altezza = h;
    reg->area = a;
}
