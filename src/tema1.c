#include "tema1.h"

void createList(N **cap, N **q, double val){
    N *p = NULL;
    p = (N*) malloc(sizeof(N));
    if(p == NULL){ 
        return;
    }
    p->valoare = val;
    p->next = NULL;
    if(*cap == NULL){
        *cap = p;
        p->randament = 0;
    }
    else{
        (*q)->next = p;
        p->randament = (p->valoare - (*q)->valoare) / (*q)->valoare;
    }
    *q = p;
}

double average(N *cap, int n){
    N *p = cap->next;
    double s = 0.0; // suma tuturor randamentelor
    while(p != NULL){
        s += p->randament;
        p = p->next;
    }
    return s / (n - 1); //prima valoare a randamentului este nedefinita
}

double volatility(N *cap, double rmediu, int n){
    double svol = 0;
    N *p = cap->next;
    while(p != NULL){
        svol += (p->randament - rmediu) * (p->randament - rmediu);
        p = p->next;
    }
    return sqrt(svol / (n - 1));
}

void freeList(N *cap){ 
    N *p = cap;
    while(p != NULL){
        N *temp = p;
        p = p->next;
        free(temp);
    } 
}

void rezolva_interviu1(FILE *in, FILE *out){
    //complexitate O(n)
    int n = 0;
    double val = 0.0;
    N *cap = NULL, *q = NULL; 
    //q retine ultimul element din lista si este folosita pt a nu parcurge lista 
    //de la cap la coada la fiecare adaugare noua
    //citire
    fscanf(in, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(in, "%lf", &val);
        createList(&cap, &q, val); //se foloseste lista pentru ca e nevoie de pretul zilei curentei si zilei anterioare
    }
    if(cap == NULL) {
        return;
    }
    //calculeaza variabile + afisare
    double rmediu = average(cap, n); //media
    fprintf(out, "%.3lf\n", (int)(rmediu * 1000.0) / 1000.0); //printf ul cu afisarea celor 3 zecimale fara aceasta formula va face o rontujire
    
    double vol = volatility(cap, rmediu, n); //volatilitatea
    fprintf(out, "%.3lf\n", (int)(vol * 1000.0) / 1000.0);
    
    double ratio = rmediu / vol; //sharpe ratio
    fprintf(out, "%.3lf\n", (int)(ratio * 1000.0) / 1000.0);
    //eliberarea memoriei
    freeList(cap);//pt a nu avea memory leak
}