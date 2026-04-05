#include "tema.h"

void createList(FILE *in, FILE *out, N **cap, double val){
    N *p = NULL, *q = NULL;
    p = (N*) malloc(sizeof(N));
    if(p == NULL){
        fclose(in);
        fclose(out);
        return 1;
    }
    p->valoare = val;
    p->next = NULL;
    if(cap == NULL){
        cap = p;
        p->randament = 0;
    }
    else{
        q->next = p;
        p->randament = (p->valoare - q->valoare) / q->valoare;
    }
    q->next = p;
    q = p;
}

double average(N *cap, int n){
    N *p = cap->next;
    double s = 0.0;
    while(p != NULL){
        s += p->randament;
        p = p->next;
    }
    return s / (n - 1);
}

double volatility(N *cap, int rmediu, int n){
    double svol = 0;
    N *p = cap->next;
    while(p != NULL){
        svol += (p->randament - rmediu) * (p->randament - rmediu);
        p = p->next;
    }
    return sqrt(svol / (n - 1));
}

void freeList(N *cap){
    N *p = cap;
    while(p != NULL){
        N *temp = p;
        p = p->next;
        free(temp);
    } 
}