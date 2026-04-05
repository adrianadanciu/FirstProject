#include "tema.h"

int main(const int argc, const char *argv[]){
    if(argc < 3){
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if(in == NULL || out == NULL){
        return 1;
    }
    int n = 0;
    double val = 0.0;
    N *cap = NULL, *q = NULL;
    fscanf(in, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(in, "%lf", &val);
        createList(&cap, &q, val);
    }
    if(cap == NULL) {
        return 1;
    }
    double rmediu = average(cap, n);
    fprintf(out, "%.3lf\n", (int)(rmediu * 1000.0) / 1000.0);
    
    double vol = volatility(cap, rmediu, n);
    fprintf(out, "%.3lf\n", (int)(vol * 1000.0) / 1000.0);
    
    double ratio = rmediu / vol;
    fprintf(out, "%.3lf\n", (int)(ratio * 1000.0) / 1000.0);

    freeList(cap);
    fclose(in);
    fclose(out);
    return 0;
}