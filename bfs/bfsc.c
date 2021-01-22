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

void computeBFS(graph g, int start, int end) {
    bool *visited = makeFalsyArray(g.order);

    int edgeCount = countEdges(g);
    int time = 0;

    edge *tree = (edge *) calloc(edgeCount + 1, sizeof(edge)); //First element stores the edge no of the current element
    tree[0].x = 1; //Tree edge no

    for(int i = 0; i < g.order; ++i) {
        g.bfsn[i] = -1;
        g.pred[i] = -1;
    }

    bfs(g, start, visited, tree, &time);

    //Print Path
    int cost = 0;
    if(g.pred[end] == -1)
        printf("There is no path from %d to %d\n", start, end);
    else {
        printf("The shortest path is: \n");
        int v = end;
        while(v != start) {
            printf("%d <- ", v);
            cost++;
            v = g.pred[v];
        }
        printf("%d | %d edges.\n", start, cost);
    }
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
    int start, end;
    printGraph(g);
    printf("Enter the start and the end vertex: ");
    scanf("%d %d", &start, &end);
    computeBFS(g, start, end);
}