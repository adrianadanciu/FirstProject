#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

struct Elem{
    double val;
    struct Elem *next;
};

typedef struct Elem S;

struct nodeq{
    char s[256];
    struct nodeq *next;
};

typedef struct nodeq NQ;

struct Q{
    NQ *front, *rear;
};

typedef struct Q Queue;

void createList(N **cap, N **q, double val);
double average(N *cap, int n);
double volatility(N *cap, double rmediu, int n);
void freeList(N *cap);


void push(S** top, double v);
int isEmptyS(const S *top);
double pop(S** top);

Queue *createQueue();
void enQueue(Queue *q, const char v[]);

void createString(double val1, double val2, double val3, char s[], int i, const char s3[]);

static int isEmptyQ(const Queue *q);
void printQueue(Queue *q, FILE *out);

void deleteStack(S** top);

void rezolva_interviu1(FILE *in, FILE *out);
void rezolva_interviu2(FILE *in, FILE *out);