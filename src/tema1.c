#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

int main(int argc, char *argv[]){
    FILE *in = fopen(argv[1], "rt");
    FILE *out = fopen(argv[2], "wt");
    int n;
    double val, s = 0;
    N *p, *q = NULL, *cap = NULL;
    fscanf(in, "%d", &n);
    fscanf(in, "%lf", &val);
    p = (N*) malloc(sizeof(N));
    p->valoare = val;
    p->randament = 0;
    cap = p;
    q = p;
    for(int i = 1; i < n; i++){
        fscanf(in, "%lf", &val);
        p = (N*) malloc(sizeof(N));
        p->valoare = val;
        p->randament = (p->valoare - q->valoare) / q->valoare;
        s += p->randament;
        q->next = p;
        q = p;
    }
    double rmediu = s / (n - 1);
    fprintf(out, "%.3lf\n", (int)(rmediu * 1000.0) / 1000.0);
    
    double svol = 0;
    p = cap->next;
    while(p != NULL){
        svol += (p->randament - rmediu) * (p->randament - rmediu);
        p = p->next;
    }
    double vol = sqrtl(svol / (n - 1));
    fprintf(out, "%.3lf\n", (int)(vol * 1000.0) / 1000.0);
    
    double ratio = rmediu / vol;
    fprintf(out, "%.3lf\n", (int)(ratio * 1000.0) / 1000.0);

    fclose(in);
    fclose(out);
    return 0;
}