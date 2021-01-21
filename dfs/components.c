#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<graph.h>

typedef struct {
    int x;
    int y;
} edge;

typedef struct {
    int dfsn;
    int dfscn;
} dfsnos;

bool* makeFalsyArray(int size) {
    bool *a = malloc(size*sizeof(bool));
    for(int i = 0; i < size; ++i)
        a[i] = false;
    return a;
}

bool dfs(graph g, int current, bool *visited) {
    if(visited[current] == true)
        return false;
    
    visited[current] = true;

    list *adj = getAdjList(&g, current);
    node *t = adj->head;
    while(t) {
        if(!visited[t->val]) {
            dfs(g, t->val, visited);
        }
        t = t->next;
    }

    return true;
}

int countComponents(graph g) {
    bool *visited = makeFalsyArray(g.order);

    int components = 0;
    int doFrom = 0;
    bool someComponentLeft = false;

    for(int i = 0; i < g.order; ++i)
        components += dfs(g, i, visited) ? 1 : 0;

    return components;
}

int main() {
    int order;
    printf("Enter the order of the graph: "); scanf("%d", &order);

    if(order <= 0) {
        printf("Incorrect order of graph. Must be > 0.");
        return -1;
    }

    graph g = createGraph(order);

    printf("Enter the edges of the graph, and -1 to stop inputting edges:\n");
    printGraph(g);
    while(true) {
        int s, e;
        printf("Enter the start and end vertices of the edge: ");
        scanf("%d %d", &s, &e);
        if(s == -1 || e == -1){
            break;
        }
        addEdge(&g, s, e);
    }
    printGraph(g);
    printf("The graph has %d components.\n", countComponents(g));
    return 1;
}