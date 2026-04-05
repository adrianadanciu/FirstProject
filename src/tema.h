#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

void createList(FILE *in, FILE *out, N *cap, double val);
double average(N *cap, int n);
double volatility(N *cap, int rmediu, int n);
void freeList(N *cap);