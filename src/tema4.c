#include "tema4.h"

static int cmmdc(int a, int b){
    while(b != 0){
        int r = a % b;
        a = b; 
        b = r;
    }
    return a;
}

static int maxx(float *zile, int n, int minn, int d){
    int max_stare = 0;
    for(int i = 0; i < n; i++) {
        int stare = floor((zile[i] - minn) / d);
        if(stare > max_stare) {
            max_stare = stare;
        }
    }
    return max_stare;
}

static void adaugare_lista(int indice_i, int indice_j, E **graf){
    E* muchie = graf[indice_i];
    int gasit = 0;
    while(muchie != NULL) {
        if(muchie->destinatie == indice_j) {
            muchie->frecventa++;
            gasit = 1;
            break;
        }
        muchie = muchie->next;
    }
    if(!gasit) {
        E* muchie_noua = (E*)malloc(sizeof(E));
        muchie_noua->destinatie = indice_j;
        muchie_noua->frecventa = 1;
        muchie_noua->next = graf[indice_i];
        graf[indice_i] = muchie_noua;
    }
}

//se calculeaza matricea de tranzitie tot sub forma unei liste de adicenta
static void tranzitie(int max_stare, E **graf, int *departures){
    for(int i = 0; i <= max_stare; i++) {
        E* muchie = graf[i];
        while(muchie != NULL) {
            int cmmdc_t = cmmdc(muchie->frecventa, departures[i]);
            muchie->probabilitate.numarator = muchie->frecventa / cmmdc_t;
            muchie->probabilitate.numitor = departures[i] / cmmdc_t;
            muchie = muchie->next;
        }
    }
}

static void initializare(int max_stare, F *P_current, F *P_next){
    for(int i = 0; i <= max_stare; i++) {
        P_current[i].numarator = 0;
        P_current[i].numitor = 1;
        P_next[i].numarator = 0;
        P_next[i].numitor = 1;
    }
}

static void eliberare_memorie(int max_stare, E **graf, int *departures, F *P_current, F *P_next, float *zile){
    for(int i = 0; i <= max_stare; i++) {
        E* current = graf[i];
        while(current != NULL) {
            E* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graf);
    free(departures);
    free(P_current);
    free(P_next);
    free(zile);
}

void rezolva_interviu4(FILE *in, FILE *out){
    int n, k, minn = INT_MAX; //n nr preturi date, k nr zile
    float d, p_start, p_target;
    fscanf(in, "%d%f%d%f%f", &n, &d, &k, &p_start, &p_target);
    float *zile = (float*)malloc(n * sizeof(float));
    for(int i = 0; i < n; i++){
        fscanf(in, "%f", &zile[i]);
        if(zile[i] < minn) //calculam minn pentru starea fiecarui pret
            minn = zile[i];
    }
    int max_stare = maxx(zile, n, minn, d);
    E **graf = (E**)calloc((max_stare + 1), sizeof(E*));
    int *departures = (int*)calloc((max_stare + 1), sizeof(int));
    F *P_current = (F*)malloc((max_stare + 1) * sizeof(F));
    F *P_next = (F*)malloc((max_stare + 1) * sizeof(F));
    for(int i = 0; i < n - 1; i++){
        int indice_i = floor((zile[i] - minn) / d), indice_j = floor((zile[i + 1] - minn) / d); 
        /*
        m[indice_i][indice_j]++; //matricea de adiacenta a starilor
        departures[indice_i]++;
        */
        adaugare_lista(indice_i, indice_j, graf);
        departures[indice_i]++;
    }
    tranzitie(max_stare, graf, departures);

    int s_start = floor((p_start - minn) / d);
    initializare(max_stare, P_current, P_next);
    P_current[s_start].numarator = 1; //probabilitatea maxima de a se afla in s_start
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
            fprintf(out, "%d", P_current[s_target].numarator); //daca e numar intreg, nu mai afisam ca fractie
        }
        else {
            fprintf(out, "%d/%d", P_current[s_target].numarator, P_current[s_target].numitor);
        }
        for(int i = 0; i <= max_stare; i++) {
            if(P_current[i].numarator > 0) {
                E* muchie = graf[i];
                while(muchie != NULL) {
                    int j = muchie->destinatie;
                    //a/b = P_next[j]
                    //c/d = P_current[i] * muchie->probabilitate
                    P_next[j].numarator = P_next[j].numarator * muchie->probabilitate.numitor * 
                    P_current[i].numitor + muchie->probabilitate.numarator * P_current[i].numarator * 
                    P_next[j].numitor;
                    P_next[j].numitor = P_next[j].numitor * muchie->probabilitate.numitor * P_current[i].numitor;
                    int cmmdc_t = cmmdc(P_next[j].numarator, P_next[j].numitor);
                    P_next[j].numarator = P_next[j].numarator / cmmdc_t;
                    P_next[j].numitor = P_next[j].numitor / cmmdc_t;

                    muchie = muchie->next;
                }
            }
        }
        for(int j = 0; j <= max_stare; j++) {
            P_current[j].numarator = P_next[j].numarator;
            P_current[j].numitor = P_next[j].numitor;
            P_next[j].numarator = 0;
            P_next[j].numitor = 1;
        }
    }
    eliberare_memorie(max_stare, graf, departures, P_current, P_next, zile);
    /*
    for(int i = 0; i <= max_stare; i++){
        for(int j = 0; j <= max_stare; j++){
            int cmmdc_t = cmmdc(m[i][j], departures[i]); //pentru a fi afisate ca fractii ireductibile
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
    P_current[s_start].numarator = 1; //probabilitatea maxima de a se afla in s_start
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
            fprintf(out, "%d", P_current[s_target].numarator); //daca e numar intreg, nu mai afisam ca fractie
        }
        else {
            fprintf(out, "%d/%d", P_current[s_target].numarator, P_current[s_target].numitor);
        }
        
        for(int i = 0; i <= max_stare; i++){
            for(int j = 0; j <= max_stare; j++){
                if(P_current[i].numarator > 0 && t[i][j].numarator > 0){
                    //a/b = P_next[j]
                    //c/d = P_current[i] * t[i][j]
                    P_next[j].numarator = P_next[j].numarator * t[i][j].numitor * P_current[i].numitor
                    + t[i][j].numarator * P_current[i].numarator * P_next[j].numitor; //axd+bxc
                    P_next[j].numitor = P_next[j].numitor * t[i][j].numitor * P_current[i].numitor;//bxd
                    int cmmdc_t = cmmdc(P_next[j].numarator, P_next[j].numitor);
                    P_next[j].numarator = P_next[j].numarator / cmmdc_t;
                    P_next[j].numitor = P_next[j].numitor / cmmdc_t;
                }
            }
        }
        for(int j = 0; j <= max_stare; j++){ //actualizare
            P_current[j].numarator = P_next[j].numarator;
            P_current[j].numitor = P_next[j].numitor;
            P_next[j].numarator = 0;
            P_next[j].numitor = 1;
        }
    }
    */
}