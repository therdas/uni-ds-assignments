#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<list.h>


node* makeNode(int val) {
    node* temp = (struct node *) malloc(sizeof(node));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

list makeList() {
    list l;
    l.head = NULL;
    return l;
}

void freeList(list *l) {
    node *t = l->head;
    while(t){
        node *temp = t->next;
        free(t);
        t = temp;
    } 
}

void addToList(list *l, int val) {
    if(l->head == NULL) {
        l->head = makeNode(val);
    } else {
        node *temp = makeNode(val);
        temp->next = l->head;
        l->head = temp;
    }
}

bool searchForNode(list l, int val){
    node *temp = l.head;

    while(temp){
        if(temp->val == val)
            return true;
        temp = temp->next;
    }

    return false;
}

int size(list l) {
    node *t = l.head;
    int size = 0;
    while(t) {
        ++size;
        t = t->next;
    }
    return size;
}