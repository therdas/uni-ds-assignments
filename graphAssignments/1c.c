#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int order;
    //int size;
    int **matrix;
} graph;

graph createGraph(int order) {
    graph g;
    g.order = order;

    g.matrix = (int **) malloc(sizeof(int *) * order);

    for(int i = 0; i < order; ++i) {
        g.matrix[i] = (int *) malloc(sizeof(int) * order);

        for(int j = 0; j < g.order; ++j)
            g.matrix[i][j] = 0;
    }

    return g;
}

void freeGraph(graph *g) {
    for(int i = 0; i < g->order; ++i)
        free(g->matrix[i]);
    free(g->matrix);
    g->order = 0;
}

bool checkBounds(graph g, int start, int end) {
    return !(start < 0 || start > g.order || end < 0 || end > g.order);
}

graph markEdge(graph g, int start, int end) {

    if(!checkBounds(g, start, end))
        return g;

    g.matrix[start][end] = 1;
    
    return g;
}

bool isEdge(graph g, int start, int end) {
    return checkBounds(g, start, end) ? g.matrix[start][end] > 0 : false;
}

void printMatrix(graph g) {
    for(int i = 0; i < g.order; ++i){
        for(int j = 0; j < g.order; ++j)
            printf("%d ", g.matrix[i][j]);
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

int main(int argc, char **argv) {
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

        g = markEdge(g, start, end);
    }

    traverseGraph(g, 0, 0, NULL);
    freeGraph(&g);
    return 0;
}