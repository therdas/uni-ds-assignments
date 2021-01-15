#ifndef _TRD_DGRAPH
#define _TRD_DGRAPH
#include<stdbool.h>
#include "list.h"


typedef struct {
    int order;
    list* vertices;
} dgraph;

dgraph createGraph(int order);
void freeGraph(dgraph *g);

bool checkBounds(dgraph g, int start, int end);

void addEdge(dgraph *g, int start, int end);
bool isEdge(dgraph g, int start, int end);

void printGraph(dgraph g);

list* getAdjList(dgraph *g, int vertex);

int countEdges(dgraph g);
#endif