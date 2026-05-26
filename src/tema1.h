#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

void createList(N **cap, N **q, double val);
double average(N *cap, int n);
double volatility(N *cap, double rmediu, int n);
void freeList(N *cap);
void rezolva_interviu1(FILE *in, FILE *out);