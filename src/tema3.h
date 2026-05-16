#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYM 5

typedef struct StockList{
    char symbol[MAX_SYM];
    struct StockList *next;
}StockList;

typedef struct TreeNode{
    StockList *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
    int depth;
}TreeNode;

static TreeNode* createNode();
static void addStock(TreeNode *root, const char *symbol);
static int getIndex(int nr, const char symbols[][MAX_SYM], const char *target);
static void freeStockList(StockList *head);
static void freeTreeNode(TreeNode *root);

void rezolva_interviu3(FILE *in, FILE *out);