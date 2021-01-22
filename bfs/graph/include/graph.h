#ifndef _TRD_GRAPH
#define _TRD_GRAPH
#include<stdbool.h>
#include "list.h"


typedef struct {
    int order;
    list* vertices;
    int *pred;
    int *bfsn;
} graph;

graph createGraph(int order);
void freeGraph(graph *g);

bool checkBounds(graph g, int start, int end);

void addEdge(graph *g, int start, int end);
bool isEdge(graph g, int start, int end);

void printGraph(graph g);

list* getAdjList(graph *g, int vertex);
int countEdges(graph g);
#endif