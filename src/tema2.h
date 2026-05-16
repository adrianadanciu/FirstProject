#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

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

static void push(S** top, double v);
static int isEmptyS(const S *top);
static double pop(S** top);

static Queue *createQueue();
static void enQueue(Queue *q, const char v[]);

static void createString(double val1, double val2, double val3, char s[], int i, const char s3[]);

static int isEmptyQ(const Queue *q);
static void printQueue(Queue *q, FILE *out);

static void deleteStack(S** top);

void rezolva_interviu2(FILE *in, FILE *out);