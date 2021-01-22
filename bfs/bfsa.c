#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<graph.h>
#include<queue.h>

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

bool bfs(graph g, int current, bool *visited, edge *tree, int *time) {
    if(visited[current] == true)
        return false;

    queue q = makeQueue(g.order);
    enqueue(&q, current);
    visited[current] = true;
    g.bfsn[current] = (*time)++;


    while(!isEmpty(q)) {
        int n = dequeue(&q);
        printf("Visited vertex %d.\n", n);
        list *l = getAdjList(&g, n);
        node *temp = l->head;
        while(temp) {
            if (!visited[temp->val])
            {
                visited[temp->val] = true;
                //Set BFSN
                g.bfsn[temp->val] = (*time)++;
                //Set Pred
                g.pred[temp->val] = n;
                //Add to Tree
                tree[tree[0].x].x = n;
                tree[tree[0].x].y = temp->val;
                //Prepare for next edge
                tree[0].x = tree[0].x + 1;

                //Enqueue
                enqueue(&q, temp->val);
            }
            temp = temp->next;
        }
    }

    return true;
}

void computeBFS(graph g) {
    bool *visited = makeFalsyArray(g.order);

    int edgeCount = countEdges(g);
    int time = 0;

    edge *tree = (edge *) calloc(edgeCount + 1, sizeof(edge)); //First element stores the edge no of the current element
    tree[0].x = 1; //Tree edge no

    for(int i = 0; i < g.order; ++i) {
        g.bfsn[i] = -1;
        g.pred[i] = -1;
    }

    for(int i = 0; i < g.order; ++i)
        bfs(g, i, visited, tree, &time);

    printf("The BFS tree is as follows: \n");
    for(int i = 1; i < tree[0].x; ++i)
        printf("{%d, %d}, ", tree[i].x, tree[i].y);
    printf("\b\b  \n\n");

    printf("The BFS numbers and predecessors are: \n");
    printf("+------+------+-------------+\n");
    printf("|Vertex| BFS# | Predecessor |\n");
    printf("|      |      | -1  => None |\n");
    printf("+------+------+-------------+\n");
    for(int i = 0; i < g.order; ++i)
        printf("| %4d | %4d | %11d |\n", i, g.bfsn[i], g.pred[i]);
    printf("+------+------+-------------+\n");
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
            break;
        }
        addEdge(&g, s, e);
    }
    printGraph(g);
    computeBFS(g);
}