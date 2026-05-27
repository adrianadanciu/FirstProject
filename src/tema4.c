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
    E* muchie = graf[indice_i]; //capul listei
    //fiecare nod din aceasta lista reprezinta o destinatie la care pretul a ajuns
    //a doua zi din indicele i
    int gasit = 0; //variabila de tip semafor care verifica daca muchia exista in graf
    while(muchie != NULL) {
        if(muchie->destinatie == indice_j) {
            muchie->frecventa++; //in acest caz, doar se creste frecventa
            gasit = 1;
            break;
        }
        muchie = muchie->next;
    }
    if(!gasit){
        //se aloca dinamic noua muchie
        E* muchie_noua = (E*)malloc(sizeof(E));
        muchie_noua->destinatie = indice_j;
        muchie_noua->frecventa = 1;
        //se adauga noua muchie la capul listei
        //se poate adauga si la finalul listei, dar ar fi in complexitate O(n) in loc de O(1)
        muchie_noua->next = graf[indice_i];
        graf[indice_i] = muchie_noua;
    }
}

//se calculeaza matricea de tranzitie tot sub forma unei liste de adicenta
static void tranzitie(int max_stare, E **graf, int *departures){
    for(int i = 0; i <= max_stare; i++) {
        E* muchie = graf[i];
        while(muchie != NULL) {
            //se foloseste cmmdc pt a scrie probabilitatea ca fractie ireductibila
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
    //complexitate O(n x M + k x M^2)
    //M = max_stare
    //construirea grafului, a listei de adiacenta e in O(n x M)
    //se parcurg cele n preturi date si, in cel mai rau caz, are M destinatii
    //calcularea probabilitatilor are loc in O(k x M^2)
    //pentru fiecare din cele k zile, trebuie verificate fiecare din cele M stari curente
    //parcurgem toate muchiile care pleaca din i
    int n, k, minn = INT_MAX; //n nr preturi date, k nr zile
    float d, p_start, p_target;
    //citire
    fscanf(in, "%d%f%d%f%f", &n, &d, &k, &p_start, &p_target);
    float *zile = (float*)malloc(n * sizeof(float));
    for(int i = 0; i < n; i++){
        fscanf(in, "%f", &zile[i]);
        if(zile[i] < minn) //calculam minn pentru starea fiecarui pret
            minn = zile[i];
    }
    int max_stare = maxx(zile, n, minn, d);
    //lantul markov este prin defintie un graf orientat
    //starile sunt noduri, iar probabilitatile de trecere muchii
    //alocarea structurilor prin care vom avea probabilitatea in fiecare zi
    E **graf = (E**)calloc((max_stare + 1), sizeof(E*)); 
    int *departures = (int*)calloc((max_stare + 1), sizeof(int));
    F *P_current = (F*)malloc((max_stare + 1) * sizeof(F));
    F *P_next = (F*)malloc((max_stare + 1) * sizeof(F));
    //calculul matricii de adiacenta
    for(int i = 0; i < n - 1; i++){
        int indice_i = floor((zile[i] - minn) / d), indice_j = floor((zile[i + 1] - minn) / d); 
        /*
        m[indice_i][indice_j]++; //matricea de adiacenta a starilor
        departures[indice_i]++;
        */
        adaugare_lista(indice_i, indice_j, graf);
        departures[indice_i]++;
    }
    //calculul matricii de tranzitie
    tranzitie(max_stare, graf, departures);

    //calculul probabilitatii in fiecare zi
    int s_start = floor((p_start - minn) / d);
    initializare(max_stare, P_current, P_next);
    P_current[s_start].numarator = 1; //probabilitatea maxima de a se afla in s_start
    P_current[s_start].numitor = 1;
    int first = 1;
    for(int day = 0; day < k; day++) {
        int s_target = floor((p_target - minn) / d);
        //afisarea
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
        //calcului lui P_next, adica probabilitatea pe ziua urmatoare
        //se face in ziua curenta pt ca este nevoie de variabila P_current
        //adica probabilitatea curenta
        //probabilitatea de a ajunge maine in starea j se calculeaza ca suma tuturor 
        //drumurilor posibile din ziua curenta in j
        //adica probabilitea sa fiu azi in starea i inmultita cu sansa de a ajunge
        //din i in j
        for(int i = 0; i <= max_stare; i++){
            if(P_current[i].numarator > 0){
                E* muchie = graf[i];
                while(muchie != NULL){
                    int j = muchie->destinatie;
                    //a/b = P_next[j]
                    //c/d = P_current[i] * muchie->probabilitate
                    P_next[j].numarator = P_next[j].numarator * muchie->probabilitate.numitor * 
                    P_current[i].numitor + muchie->probabilitate.numarator * P_current[i].numarator * 
                    P_next[j].numitor; //axd+bxc
                    P_next[j].numitor = P_next[j].numitor * muchie->probabilitate.numitor * P_current[i].numitor;//bxd
                    //se foloseste cmmdc pt a scrie probabilitatea ca fractie ireductibila
                    int cmmdc_t = cmmdc(P_next[j].numarator, P_next[j].numitor);
                    P_next[j].numarator = P_next[j].numarator / cmmdc_t;
                    P_next[j].numitor = P_next[j].numitor / cmmdc_t;

                    muchie = muchie->next;
                }
            }
        }
        //actualizarea variabilei P_current si reinitializarea lui P_next
        for(int j = 0; j <= max_stare; j++) {
            P_current[j].numarator = P_next[j].numarator;
            P_current[j].numitor = P_next[j].numitor;
            P_next[j].numarator = 0;
            P_next[j].numitor = 1;
        }
    }
    //eliberarea memoriei
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