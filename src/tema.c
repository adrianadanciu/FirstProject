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

void rezolva_interviu1(FILE *in, FILE *out){
    int n = 0;
    double val = 0.0;
    N *cap = NULL, *q = NULL;
    fscanf(in, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(in, "%lf", &val);
        createList(&cap, &q, val);
    }
    if(cap == NULL) {
        return;
    }
    double rmediu = average(cap, n);
    fprintf(out, "%.3lf\n", (int)(rmediu * 1000.0) / 1000.0);
    
    double vol = volatility(cap, rmediu, n);
    fprintf(out, "%.3lf\n", (int)(vol * 1000.0) / 1000.0);
    
    double ratio = rmediu / vol;
    fprintf(out, "%.3lf\n", (int)(ratio * 1000.0) / 1000.0);

    freeList(cap);
}

void rezolva_interviu2(FILE *in, FILE *out){
    S *stacktop1 = NULL, *stacktop2 = NULL, *stacktop3 = NULL;
    char s[256], s1[256] = "", s2[256] = "", s3[256] = "";
    int i = 0;
    Queue *q = createQueue();
    while(fgets(s, 256, in)){
        s[strcspn(s, "\r\n")] = 0;
        if(isalpha(s[0])){
            i++;
            if(i == 1)
                strcpy(s1, s);
            if(i == 2)
                strcpy(s2, s);
            if(i == 3)
                strcpy(s3, s);
        }
        else{
            double nr = atof(s);
            if(i == 1){
                push(&stacktop1, nr);
            }
            if(i == 2){
                push(&stacktop2, nr);
            }
            if(i == 3){
                push(&stacktop3, nr);
            }
        }
    }
    i = 0; //ziua
    while(!isEmptyS(stacktop1) && !isEmptyS(stacktop2) && !isEmptyS(stacktop3)){
        i++;
        double val1 = pop(&stacktop1), val2 = pop(&stacktop2), val3 = pop(&stacktop3);
        char rasp[256] = "ziua ";
        if(val1 == val2 && val1 != val3){
            createString(val1, val2, val3, rasp, i, s3);
            enQueue(q, rasp);
        }
        if(val2 == val3 && val2 != val1){
            createString(val2, val3, val1, rasp, i, s1);
            enQueue(q, rasp);
        }
        if(val1 == val3 && val1 != val2){
            createString(val1, val3, val2, rasp, i, s2);
            enQueue(q, rasp);
        }
    }
    printQueue(q, out);
    deleteStack(&stacktop1);
    deleteStack(&stacktop2);
    deleteStack(&stacktop3);
}