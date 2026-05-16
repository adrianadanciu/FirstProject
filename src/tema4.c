#include "tema4.h"

static int cmmdc(int a, int b){
    while(b != 0){
        int r = a % b;
        a = b; 
        b = r;
    }
    return a;
}

void rezolva_interviu4(FILE *in, FILE *out){
    int n, k, m[50][50] = {}, minn = INT_MAX, departures[50] = {};
    F t[50][50];
    float d, p_start, p_target, zile[50];
    fscanf(in, "%d%f%d%f%f", &n, &d, &k, &p_start, &p_target);
    for(int i = 0; i < n; i++){
        fscanf(in, "%f", &zile[i]);
        if(zile[i] < minn)
            minn = zile[i];
    }
    int max_stare = 0;
    for(int i = 0; i < n - 1; i++){
        int indice_i = floor((zile[i] - minn) / d), indice_j = floor((zile[i + 1] - minn) / d);
        if(indice_i > max_stare)
            max_stare = indice_i;
        if(indice_j > max_stare)
            max_stare = indice_j;    
        m[indice_i][indice_j]++; 
        departures[indice_i]++;
    }
    for(int i = 0; i <= max_stare; i++){
        for(int j = 0; j <= max_stare; j++){
            int cmmdc_t = cmmdc(m[i][j], departures[i]);
            t[i][j].numarator = m[i][j] / cmmdc_t;
            t[i][j].numitor = departures[i] / cmmdc_t;
        }
    }
    int s_start = floor((p_start - minn) / d);
    F P_current[50], P_next[50];
    for(int i = 0; i <= max_stare; i++){
        P_current[i].numarator = 0;
        P_current[i].numitor = 1;
        P_next[i].numarator = 0;
        P_next[i].numitor = 1;
    }
    P_current[s_start].numarator = 1;
    P_current[s_start].numitor = 1;

    int first = 1;
    for(int day = 0; day < k; day++) {
        int s_target = floor((p_target - minn) / d);
        if(!first) {
            fprintf(out, "\n");
        }
        else {
            first = 0;
        }
        if(P_current[s_target].numitor == 1) {
            fprintf(out, "%d", P_current[s_target].numarator);
        }
        else {
            fprintf(out, "%d/%d", P_current[s_target].numarator, P_current[s_target].numitor);
        }
        
        for(int i = 0; i <= max_stare; i++){
            for(int j = 0; j <= max_stare; j++){
                if(P_current[i].numarator > 0 && t[i][j].numarator > 0){
                    P_next[j].numarator = P_next[j].numarator * t[i][j].numitor * P_current[i].numitor
                    + t[i][j].numarator * P_current[i].numarator * P_next[j].numitor;
                    P_next[j].numitor = P_next[j].numitor * t[i][j].numitor * P_current[i].numitor;
                    int cmmdc_t = cmmdc(P_next[j].numarator, P_next[j].numitor);
                    P_next[j].numarator = P_next[j].numarator / cmmdc_t;
                    P_next[j].numitor = P_next[j].numitor / cmmdc_t;
                }
            }
        }
        for(int j = 0; j <= max_stare; j++){
            P_current[j].numarator = P_next[j].numarator;
            P_current[j].numitor = P_next[j].numitor;
            P_next[j].numarator = 0;
            P_next[j].numitor = 1;
        }
    }
}