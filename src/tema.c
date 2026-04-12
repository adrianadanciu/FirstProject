#include "tema.h"

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
    double s = 0.0;
    while(p != NULL){
        s += p->randament;
        p = p->next;
    }
    return s / (n - 1);
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


void push(S** top, double v){
    S* newNode = (S*)malloc(sizeof(S));
    if(newNode == NULL)
        return;
    newNode->val = v;
    newNode->next = *top;
    *top = newNode;
}

int isEmptyS(const S *top){
    return top == NULL;
}

double pop(S** top){
    if(isEmptyS(*top))
        return INT_MIN;
    S *temp = *top;
    double aux = temp->val;
    *top = (*top)->next;
    free(temp);
    return aux;
}

Queue *createQueue(){
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if(q == NULL){
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue *q, const char v[]){
    NQ* newNode = (NQ*) malloc(sizeof(NQ));
    if(newNode == NULL)
        return;
    strcpy(newNode->s, v);
    newNode->next = NULL;
    if(q->rear == NULL)
        q->rear = newNode;
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    if(q->front == NULL)
        q->front = q->rear;
}

void createString(double val1, double val2, double val3, char s[], int i, const char s3[]){
    char aux[20];
    sprintf(aux, "%d", i);
    strcat(s, aux);
    strcat(s, " - ");
    double dif = fabs(val3 - val1);
    char sdif[256];
    sprintf(sdif, "%.2lf", dif);
    strcat(s, sdif);
    strcat(s, " - ");
    strcat(s, s3);
}

static int isEmptyQ(const Queue *q){
    return q->front == NULL;
}

void printQueue(Queue *q, FILE *out){
    NQ *aux = NULL;
    while(!isEmptyQ(q)){
        aux = q->front;
        fprintf(out, "%s\n", aux->s);
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}

void deleteStack(S** top){
    while(*top != NULL){
        S* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}