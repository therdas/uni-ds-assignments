#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int order;
    int size;
    int **matrix;
} graph;

graph createGraph(int order) {
    graph g;
    g.order = order;
    g.size = 0;                         //Initially null graph 

    g.matrix = (int **) malloc(sizeof(int *) * order);
    for(int i = 0; i < order; ++i) {
        g.matrix[i] = NULL;             //add edges dynamically.
    }

    return g;
}

void freeGraph(graph *g) {
    if(g->size > 0) {
        for(int i = 0; i < g->order; ++i)
            free(g->matrix[i]);
    }
    free(g->matrix);
    g->order = g->size = 0;
}

bool checkBounds(graph g, int start, int end) {
    return !(start < 0 || start >= g.order || end < 0 || end >= g.order);
}

int addEdge(graph *g, int start, int end) {
    if(!checkBounds(*g, start, end))
        return -1;
    
    g->size++;
    if(g->size == 1)     //First edge added
        for(int i = 0; i < g->order; ++i) 
            g->matrix[i] = malloc(sizeof(int) * g->size);
    else
        for(int i = 0; i < g->order; ++i)
            g->matrix[i] = realloc(g->matrix[i], sizeof(int) * g->size);

    g->matrix[start][g->size - 1] = 1;
    g->matrix[end][g->size - 1] = 1;

    return g->size - 1;
}

bool isEdge(graph g, int start, int end) {
    if(!checkBounds(g, start, end))
        return false;
    
    for(int j = 0; j <= g.size; ++j)
        if(g.matrix[start][j] > 0 && g.matrix[end][j] > 0)
            return true;
    
    return false;
}

int printMatrix(graph g) {
    for(int i = 0; i < g.order; ++i) {
        for(int j = 0; j < g.size; ++j)
            printf("%3d", g.matrix[i][j]);
        printf("\n");
    }
}

bool* createFalsyBoolArray(int size) {
    bool *a = malloc(size*sizeof(bool));
    for(int i = 0; i < size; ++i)
        a[i] = false;
    return a;
}

void traverseGraph(graph g, int start, int increment, bool visited[]) {
    if(!visited) visited = createFalsyBoolArray(g.order);

    if(!checkBounds(g, start, 1))
        return;

    printf("Vertex %d visited\n", start + increment);
    visited[start] = true;

    for(int i = 0; i < g.order; ++i)
        if(!visited[i] && isEdge(g, start, i))
            traverseGraph(g, i, increment, visited);
}

int main() {
    int order;
    printf("Enter the order of the graph: ");
    scanf("%d", &order);
    printf("Enter -1 to stop and traverse.");

    graph g = createGraph(order);

    while(true) {
        int start, end;
        printf("Start Vertex (0, order-1)): ");
        scanf("%d", &start);
        if(start == -1) break;

        printf("  End Vertex (0, order-1)): ");
        scanf("%d", &end);
        if(end == -1) break;

        addEdge(&g, start, end);
    }

    traverseGraph(g, 0, 0, NULL);
    freeGraph(&g);
    return 0;
}