#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out);
void rezolva_bonus(double *prices, int n, FILE *out);