#include "tema.h"

int main(int argc, char *argv[]) {
    if(argc < 3) return 1;
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if(in == NULL || out == NULL) return 1;
    int numar_test = 0;
    const char *p = argv[1];
    while(*p){
        if(isdigit(*p)){
            numar_test = atoi(p);
            break;
        }
        p++;
    }
    if(numar_test >= 1 && numar_test <= 5)
        rezolva_interviu1(in, out);
    else if(numar_test >= 6 && numar_test <= 10)
        rezolva_interviu2(in, out);
    fclose(in);
    fclose(out);
    return 0;
}