#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

static void createList(N **cap, N **q, double val);
static double average(N *cap, int n);
static double volatility(N *cap, double rmediu, int n);
static void freeList(N *cap);
void rezolva_interviu1(FILE *in, FILE *out);