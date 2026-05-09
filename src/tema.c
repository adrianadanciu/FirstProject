#include "tema.h"

static void createList(N **cap, N **q, double val){
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

static double average(N *cap, int n){
    N *p = cap->next;
    double s = 0.0;
    while(p != NULL){
        s += p->randament;
        p = p->next;
    }
    return s / (n - 1);
}

static double volatility(N *cap, double rmediu, int n){
    double svol = 0;
    N *p = cap->next;
    while(p != NULL){
        svol += (p->randament - rmediu) * (p->randament - rmediu);
        p = p->next;
    }
    return sqrt(svol / (n - 1));
}

static void freeList(N *cap){
    N *p = cap;
    while(p != NULL){
        N *temp = p;
        p = p->next;
        free(temp);
    } 
}


static void push(S** top, double v){
    S* newNode = (S*)malloc(sizeof(S));
    if(newNode == NULL)
        return;
    newNode->val = v;
    newNode->next = *top;
    *top = newNode;
}

static int isEmptyS(const S *top){
    return top == NULL;
}

static double pop(S** top){
    if(isEmptyS(*top))
        return INT_MIN;
    S *temp = *top;
    double aux = temp->val;
    *top = (*top)->next;
    free(temp);
    return aux;
}

static Queue *createQueue(){
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if(q == NULL){
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

static void enQueue(Queue *q, const char v[]){
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

static void createString(double val1, double val2, double val3, char s[], int i, const char s3[]){
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

static void printQueue(Queue *q, FILE *out){
    NQ *aux = NULL;
    while(!isEmptyQ(q)){
        aux = q->front;
        fprintf(out, "%s\n", aux->s);
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}

static void deleteStack(S** top){
    while(*top != NULL){
        S* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

static TreeNode* createNode(int depth){
    TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
    if(newNode == NULL)
        return NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->depth = depth;
    newNode->stocks = NULL;
    return newNode;
}

static void addStock(TreeNode *root, const char *symbol){
    StockList *node = (StockList*) malloc(sizeof(StockList));
    if(node == NULL)
        return;
    strcpy(node->symbol, symbol);
    node->next = NULL;
    if(root->stocks == NULL){
        root->stocks = node;
    }
    else{
        StockList *p = root->stocks;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = node;
    }
}

static int getIndex(int nr, const char symbols[][MAX_SYM], const char *target){
    for(int i = 0; i < nr; i++){
        if(strcmp(symbols[i], target) == 0)
            return i;
    }
    return -1;
}

static void freeStockList(StockList *head){
    StockList *p = head;
    while(p != NULL){
        StockList *aux = p;
        p = p->next;
        free(aux);
    }
}

static void freeTreeNode(TreeNode *root){
    if(root == NULL)
        return;
    freeTreeNode(root->left);
    freeTreeNode(root->right);
    freeStockList(root->stocks);
    free(root);
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

void rezolva_interviu3(FILE *in, FILE *out){
    char line[1024], symbols[100][MAX_SYM];
    int nr = 0, days = 0;
    double prices[500][100];
    if(fgets(line, 1024, in)){
        //fprintf(out, "%s\n", line);
        const char *p = strtok(line, ",\n\r");
        while(p != NULL){
            strcpy(symbols[nr++], p);
            p = strtok(NULL, ",\n\r");
        }
    }
    while(fgets(line, 1024, in)){
        int cnt = 0; 
        const char *p = strtok(line, ",\n\r");
        while(p != NULL){
            prices[days][cnt++] = atof(p);
            p = strtok(NULL, ",\n\r");
        }
        if(cnt > 0){
            days++;
        }
    }
    TreeNode *root = createNode(1);
    for(int i = 0; i < nr; i++){
        TreeNode *curr = root;
        addStock(curr, symbols[i]);
        for(int j = 1; j < days; j++){
            if(prices[j][i] >= prices[j - 1][i]){
                if(curr->right == NULL)
                    curr->right = createNode(j + 1);
                curr = curr->right;
            }
            else{
                if(curr->left == NULL)
                    curr->left = createNode(j + 1);
                curr = curr->left;
            }
            addStock(curr, symbols[i]);
        }
    }
    //aflam oglinditul
    int first = 1;
    for(int i = 0; i < nr; i++){
        TreeNode *curr = root;
        int found = 1;
        for(int j = 1; j < days; j++){
            if(prices[j][i] >= prices[j - 1][i]){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
            if(curr == NULL){
                found = 0;
                break;
            }
        }
        if(found){
            StockList *p = curr->stocks;
            while(p != NULL){
                int iop = getIndex(nr, symbols, p->symbol);
                if(i < iop){
                    if(!first)
                        fprintf(out, "\n");
                    fprintf(out, "%s-%s", symbols[i], p->symbol);
                    first = 0;
                }
                p = p->next;
            }
        }
    }
    freeTreeNode(root);
}