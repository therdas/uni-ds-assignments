#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<list.h>
#include<dgraph.h>

dgraph createGraph(int order) {
    dgraph g;
    g.order = order;
    g.vertices = (list *) malloc(sizeof(list *) * order);
    for(int i = 0; i < g.order; ++i)
        g.vertices[i] = makeList();
    return g;
}

void freeGraph(dgraph *g) {
    for(int i = 0; i < g->order; ++i)
        freeList(&g->vertices[i]);
    free(g->vertices);
    g->order = 0;
}

bool checkBounds(dgraph g, int start, int end) {
    return !((start < 0) || (start >= g.order) || (end < 0) || (end >= g.order));
}

void addEdge(dgraph *g, int start, int end) {
    if(!checkBounds(*g, start, end))
        return;
    addToList(&g->vertices[start], end);
}

bool isEdge(dgraph g, int start, int end) {
    if(!checkBounds(g, start, end))
        return false;
    
    return searchForNode(g.vertices[start], end);
}

void printGraph(dgraph g) {
    for(int i = 0; i < g.order; ++i) {
        printf(" [%3d] ::  ", i);
        node *temp = g.vertices[i].head;
        while(temp) {
            printf("%3d, ", temp->val);
            temp = temp -> next;
        }
        printf("\b\b  \n");
    }
}

list* getAdjList(dgraph *g, int vertex) {
    if(!checkBounds(*g, vertex, 0))
        return NULL;
    
    return &g->vertices[vertex];
}

int countEdges(dgraph g) {
    int count = 0;

    for(int i = 0; i < g.order; ++i)
        count += size(*g.vertices);
    
    return count;
}