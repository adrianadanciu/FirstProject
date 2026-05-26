#include "tema3.h"

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

void rezolva_interviu3(FILE *in, FILE *out){
    char line[1024], symbols[100][MAX_SYM];
    int nr = 0, days = 0; //nr numarul de actiuni
    double prices[500][100];
    if(fgets(line, 1024, in)){ //linia cu numele actiunilor
        //fprintf(out, "%s\n", line);
        const char *p = strtok(line, ",\n\r");
        while(p != NULL){
            strcpy(symbols[nr++], p);
            p = strtok(NULL, ",\n\r");
        }
    }
    while(fgets(line, 1024, in)){ //liniile cu valorile
        int cnt = 0; 
        const char *p = strtok(line, ",\n\r");
        while(p != NULL){
            prices[days][cnt++] = atof(p); //de la caracter la float
            p = strtok(NULL, ",\n\r");
        }
        if(cnt > 0){
            days++;
        }
    }
    TreeNode *root = createNode(1);
    //pentru fiecare actiune am adaugat in locul ei respectiv, in fiecare zi, adica la fiecare nivel
    for(int i = 0; i < nr; i++){
        TreeNode *curr = root;
        addStock(curr, symbols[i]); //in prima zi toate actiunile apar in root
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
            if(prices[j][i] >= prices[j - 1][i]){ //parcurs in oglinda
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
        //daca oglindtul e gasit, se ia fiecare actiune a oglindintului si se asociaza pe rand cu actiunea curenta
        if(found){
            StockList *p = curr->stocks;
            while(p != NULL){
                int iop = getIndex(nr, symbols, p->symbol);
                if(i < iop){ //evit afisarea duplicatelor
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