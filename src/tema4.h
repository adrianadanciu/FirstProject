#include <stdio.h>
#include <limits.h>
#include <math.h>

struct fraction{
    int numarator, numitor;
};

typedef struct fraction F;

static int cmmdc(int a, int b);
void rezolva_interviu4(FILE *in, FILE *out);
