#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<queue.h>
#include<limits.h>

static qnode* makeNode(int val) {
    qnode* temp = (struct qnode *) malloc(sizeof(qnode));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

queue makeQueue() {
    queue l;
    l.head = NULL;
    l.tail = NULL;
    return l;
}

void freeQueue(queue *l) {
    qnode *t = l->head;
    while(t){
        qnode *temp = t->next;
        free(t);
        t = temp;
    } 
}

void enqueue(queue *l, int val) {
    if(l->head == NULL) {
        l->head = makeNode(val);
        l->tail = l->head;
    } else {
        qnode *temp = makeNode(val);
        l->tail->next = temp;
        l->tail = temp;
    }
}

int dequeue(queue *l) {
    if(l->head == NULL)
        return INT_MIN;
    
    int temp = l->head->val;
    qnode *t = l->head;
    l->head = l->head->next;
    free(t);

    if(l->head == NULL) l->tail = NULL;

    return temp;
}

static bool searchForNode(queue l, int val){
    qnode *temp = l.head;

    while(temp){
        if(temp->val == val)
            return true;
        temp = temp->next;
    }

    return false;
}

static int size(queue l) {
    qnode *t = l.head;
    int size = 0;
    while(t) {
        ++size;
        t = t->next;
    }
    return size;
}

bool isEmpty(queue l) {
    if(l.head == l.tail && l.head == NULL)
        return true;
    return false;
}