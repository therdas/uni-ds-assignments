#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<graph.h>

typedef struct {
    int x;
    int y;
} edge;

bool* makeFalsyArray(int size) {
    bool *a = malloc(size*sizeof(bool));
    for(int i = 0; i < size; ++i)
        a[i] = false;
    return a;
}

void dfs(graph g, int current, bool *visited, edge *tree) {
    printf("Visited vertex %d\n", current);
    visited[current] = true;

    list *adj = getAdjList(&g, current);
    node *t = adj->head;
    while(t) {
        printf("AT %d CONSIDERING %d\n", current, t->val);
        if(!visited[t->val]) {
            printf("YES TAKEN @ %d\n", tree[0].x);
            tree[tree[0].x].x = current;
            tree[tree[0].x].y = t->val;
            tree[0].x = tree[0].x + 1;
            dfs(g, t->val, visited, tree);
        }
        t = t->next;
    }
}

void computeDFS(graph g, int start) {
    bool *visited = makeFalsyArray(g.order);

    if(!checkBounds(g, start, 0)) return;

    int edgeCount = countEdges(g);

    edge *tree = (edge *) malloc(sizeof(edge) * (edgeCount + 1)); //First element stores the DFS# of the current element
    tree[0].x = 1; //DFS#

    dfs(g, start, visited, tree);

    for(int i = 1; i <= edgeCount; ++i)
        printf("{%d, %d}, ", tree[i].x, tree[i].y);

}

int main(int argc, char **argv) {
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
            printf("BREAKING...");
            break;
        }
        addEdge(&g, s, e);
        printf("WHAT");
    }
    printf("OUT OF INPUT LOOP");
    printGraph(g);
    computeDFS(g, 0);
}