#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_SYM 5

struct Node{
    double valoare;
    double randament;
    struct Node* next;
};

typedef struct Node N;

struct Elem{
    double val;
    struct Elem *next;
};

typedef struct Elem S;

struct nodeq{
    char s[256];
    struct nodeq *next;
};

typedef struct nodeq NQ;

struct Q{
    NQ *front, *rear;
};

typedef struct Q Queue;

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

static void createList(N **cap, N **q, double val);
static double average(N *cap, int n);
static double volatility(N *cap, double rmediu, int n);
static void freeList(N *cap);


static void push(S** top, double v);
static int isEmptyS(const S *top);
static double pop(S** top);

static Queue *createQueue();
static void enQueue(Queue *q, const char v[]);

static void createString(double val1, double val2, double val3, char s[], int i, const char s3[]);

static int isEmptyQ(const Queue *q);
static void printQueue(Queue *q, FILE *out);

static void deleteStack(S** top);

static TreeNode* createNode();
static void addStock(TreeNode *root, const char *symbol);
static int getIndex(int nr, const char symbols[][MAX_SYM], const char *target);
static void freeStockList(StockList *head);
static void freeTreeNode(TreeNode *root);

void rezolva_interviu1(FILE *in, FILE *out);
void rezolva_interviu2(FILE *in, FILE *out);
void rezolva_interviu3(FILE *in, FILE *out);