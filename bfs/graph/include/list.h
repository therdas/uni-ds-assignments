#ifndef _TRD_LIST
#define _TRD_LIST
#include<stdbool.h>

typedef struct node node;

struct node{
    int val;
    node *next;
};

typedef struct {
        struct node* head;
} list;

list makeList();
void freeList(list *l);
void addToList(list *l, int val);
int size(list l);
bool searchForNode(list l, int val);

#endif