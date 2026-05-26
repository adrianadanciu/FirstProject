#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct fraction{
    int numarator, numitor;
};

typedef struct fraction F;

struct Edge{
    int destinatie;
    int frecventa;    
    F probabilitate;    
    struct Edge* next;
};

typedef struct Edge E;

static int cmmdc(int a, int b);
static int maxx(float *zile, int n, int minn, int d);
static void adaugare_lista(int indice_i, int indice_j, E **graf);
static void tranzitie(int max_stare, E **graf, int *departures);
static void initializare(int max_stare, F *P_current, F *P_next);
static void eliberare_memorie(int max_stare, E **graf, int *departures, F *P_current, F *P_next, float *zile);

void rezolva_interviu4(FILE *in, FILE *out);
