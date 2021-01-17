#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<dgraph.h>

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

void dfs(dgraph g, int current, bool *visited, edge *tree, dfsnos *dn) {
    printf("Visited vertex %d\n", current);

    visited[current] = true;
    dn[current].dfsn = tree[0].x;

    list *adj = getAdjList(&g, current);
    node *t = adj->head;
    while(t) {
        if(!visited[t->val]) {
            tree[tree[0].x].x = current;
            tree[tree[0].x].y = t->val;
            tree[0].x = tree[0].x + 1;
            dfs(g, t->val, visited, tree, dn);
        }
        t = t->next;
    }

    dn[current].dfscn = tree[0].y;
    tree[0].y = tree[0].y + 1;
}

void computeDFS(dgraph g, int start) {
    bool *visited = makeFalsyArray(g.order);

    if(!checkBounds(g, start, 0)) return;

    int edgeCount = countEdges(g);

    edge *tree = (edge *) calloc(edgeCount + 1, sizeof(edge)); //First element stores the DFS# of the current element
    dfsnos *dn = (dfsnos *) calloc(g.order, sizeof(dfsnos));

    tree[0].x = 1; //DFS#
    tree[0].y = 1; //DFSC#

    dfs(g, start, visited, tree, dn);

    printf("The DFS tree is as follows: \n");
    for(int i = 1; i <= tree[0].x; ++i)
        printf("{%d, %d}, ", tree[i].x, tree[i].y);
    printf("\b\b  \n\n");

    printf("The DFS numbers are: (0 indicates that that vertex hasn't been visited) \n");
    printf("+------+------+-----------------+\n");
    printf("|Vertex| DFS# | DFS Completion# |\n");
    printf("+------+------+-----------------+\n");
    for(int i = 0; i < g.order; ++i)
        printf("| %4d | %4d | %15d |\n", i, dn[i].dfsn, dn[i].dfscn);
    printf("+------+------+-----------------+\n");
}

int main(int argc, char **argv) {
    int order;
    printf("Enter the order of the graph: "); scanf("%d", &order);

    if(order <= 0) {
        printf("Incorrect order of graph. Must be > 0.");
        return -1;
    }

    dgraph g = createGraph(order);

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
    computeDFS(g, 0);
}