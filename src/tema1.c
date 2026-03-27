#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

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
    double val = 0.0, s = 0.0;
    N *p, *q = NULL, *cap = NULL;
    fscanf(in, "%d", &n);
    fscanf(in, "%lf", &val);
    p = (N*) malloc(sizeof(N));
    if(p == NULL){
        return 1;
    }
    p->valoare = val;
    p->randament = 0;
    p->next = NULL;
    cap = p;
    q = p;
    for(int i = 1; i < n; i++){
        fscanf(in, "%lf", &val);
        p = (N*) malloc(sizeof(N));
        if(p == NULL){
            return 1;
        }
        p->valoare = val;
        p->randament = (p->valoare - q->valoare) / q->valoare;
        p->next = NULL;
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
    double vol = sqrt(svol / (n - 1));
    fprintf(out, "%.3lf\n", (int)(vol * 1000.0) / 1000.0);
    
    double ratio = rmediu / vol;
    fprintf(out, "%.3lf\n", (int)(ratio * 1000.0) / 1000.0);

    p = cap;
    while(p != NULL){
        N *temp = p;
        p = p->next;
        free(temp);
    }
    fclose(in);
    fclose(out);
    return 0;
}