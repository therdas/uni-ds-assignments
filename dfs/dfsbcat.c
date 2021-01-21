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

bool dfs(dgraph g, int current, bool *visited, edge *tree, dfsnos *dn) {
    if(visited[current] == true)
        return false;

    printf("Visited vertex %d\n", current);

    visited[current] = true;
    dn[current + 1].dfsn = dn[0].dfsn++;

    list *adj = getAdjList(&g, current);
    node *t = adj->head;
    while(t) {
        if(!visited[t->val]) {
            tree[tree[0].x].x = current;
            tree[tree[0].x].y = t->val;
            tree[0].x = tree[0].x + 1;
            printf("Going from %d to %d\n", current, t->val);
            dfs(g, t->val, visited, tree, dn);
        }
        t = t->next;
    }

    dn[current + 1].dfscn = dn[0].dfscn++;

    return true;
}

bool checkIfInTree(edge t[], int x, int y) {
    for(int i = 1; i <= t[0].x; ++i)
        if(t[i].x == x && t[i].y == y)
            return true;
    return false;
}
void computeDFS(dgraph g) {
    bool *visited = makeFalsyArray(g.order);

    int edgeCount = countEdges(g);

    edge *tree = (edge *) calloc(edgeCount + 1, sizeof(edge)); //First element stores the edge no of the current element
    dfsnos *dn = (dfsnos *) calloc(g.order + 1, sizeof(dfsnos));//First element stores DFS# and DFSC#

    tree[0].x = 1; //Tree edge no
    dn[0].dfsn = 1; //DFSC#
    dn[0].dfscn = 1;

    for(int i = 0; i < g.order; ++i)
        dfs(g, i, visited, tree, dn);

    for(int i = 1; i < tree[0].x; ++i)
        printf("{%d, %d} is a tree edge.\n", tree[i].x, tree[i].y);
    
    

    for(int i = 0; i < g.order; ++i) {
        
        list *adj_i = getAdjList(&g, i);
        node *t = adj_i->head;
        while(t) {
            if(!checkIfInTree(tree, i, t->val)) {
                int start = i + 1, end = t->val + 1;
                if(dn[start].dfsn < dn[end].dfsn && dn[start].dfscn > dn[end].dfscn)
                    printf("{%d, %d} is a forward edge.\n", start - 1, end - 1);
                else if(dn[start].dfsn > dn[end].dfsn && dn[start].dfscn < dn[end].dfscn)
                    printf("{%d, %d} is a back edge.\n", start - 1, end - 1);
                else
                    printf("{%d, %d} is a cross edge.\n", start - 1, end - 1);
            }
            t = t->next;
        }
    }

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
    computeDFS(g);
}