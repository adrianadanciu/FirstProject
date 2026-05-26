#include "tema1.h"
#include "tema2.h"
#include "tema3.h"
#include "tema4.h"
#include "temabonus.h"

int main(int argc, const char *argv[]) {
    if(argc < 3) return 1;
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if(in == NULL || out == NULL) return 1;
    int numar_test = 0;
    const char *p = argv[1];
    while(*p){
        if(isdigit(*p)){
            numar_test = atoi(p);
            break;
        }
        p++;
    }
    if(numar_test >= 1 && numar_test <= 5)
        rezolva_interviu1(in, out);
    else if(numar_test >= 6 && numar_test <= 10)
        rezolva_interviu2(in, out);
    else if(numar_test >= 11 && numar_test <= 15)
        rezolva_interviu3(in, out);
    else if(numar_test >= 16 && numar_test <= 20)
        rezolva_interviu4(in, out);
    else{
        int count = 0;
        const char *symbol = "AAPL"; 
        const char *interval = "1d"; 
        const char *range = "1mo";
        double *prices = get_open_prices(symbol, interval, range, &count);
        if(prices != NULL && count > 0){
            rezolva_bonus(prices, count, out);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}