#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<list.h>
#include<graph.h>
graph createGraph(int order) {
    graph g;
    g.order = order;
    g.vertices = (list *) malloc(sizeof(list) * order);
    for(int i = 0; i < g.order; ++i)
        g.vertices[i] = makeList();
    g.pred = (int *) malloc(sizeof(int) * order);
    g.bfsn = (int *) malloc(sizeof(int) * order);
    return g;
}

void freeGraph(graph *g) {
    for(int i = 0; i < g->order; ++i)
        freeList(&g->vertices[i]);
    free(g->vertices);
    g->order = 0;
    free(g->pred);
    free(g->bfsn);
}

bool checkBounds(graph g, int start, int end) {
    return !((start < 0) || (start >= g.order) || (end < 0) || (end >= g.order));
}

void addEdge(graph *g, int start, int end) {
    if(!checkBounds(*g, start, end))
        return;
    addToList(&g->vertices[start], end);
    addToList(&g->vertices[end], start); 
}

bool isEdge(graph g, int start, int end) {
    if(!checkBounds(g, start, end))
        return false;
    
    return searchForNode(g.vertices[start], end);
}

void printGraph(graph g) {
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

list* getAdjList(graph *g, int vertex) {
    if(!checkBounds(*g, vertex, 0))
        return NULL;
    
    return &g->vertices[vertex];
}

int countEdges(graph g) {
    int count = 0;

    for(int i = 0; i < g.order; ++i)
        count += size(g.vertices[i]);
    
    return count/2;
}