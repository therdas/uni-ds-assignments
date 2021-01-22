#ifndef _TRD_QUEUE
#define _TRD_QUEUE
#include<stdbool.h>

typedef struct qnode qnode;
struct qnode{
    int val;
    qnode *next;
};


typedef struct{
        qnode* head;
        qnode* tail;
} queue;

queue makeQueue();
void freeQueue(queue *);
void enqueue(queue*, int);
int dequeue(queue*);
bool isEmpty(queue);

#endif