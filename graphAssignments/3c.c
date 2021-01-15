#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int val;
    struct node *next;
} node;

typedef struct {
        node* head;
} list;

node* makeNode(int val) {
    node* temp = (node *) malloc(sizeof(node));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

list makeList() {
    list l;
    l.head = NULL;
    return l;
}

list freeList(list *l) {
    node *t = l->head;
    while(t){
        node *temp = t->next;
        free(t);
        t = temp;
    } 
}

void addToList(list *l, int val) {
    if(l->head == NULL) {
        l->head = makeNode(val);
    } else {
        node *temp = makeNode(val);
        temp->next = l->head;
        l->head = temp;
    }
}

bool searchForNode(list l, int val){
    node *temp = l.head;

    while(temp){
        if(temp->val == val)
            return true;
        temp = temp->next;
    }

    return false;
}

typedef struct {
    int order;
    list* vertices;
} graph;

graph createGraph(int order) {
    graph g;
    g.order = order;
    g.vertices = (list *) malloc(sizeof(list) * order);
    for(int i = 0; i < g.order; ++i)
        g.vertices[i] = makeList();
    return g;
}

void freeGraph(graph *g) {
    for(int i = 0; i < g->order; ++i)
        freeList(&g->vertices[i]);
    free(g->vertices);
    g->order = 0;
}

bool checkBounds(graph g, int start, int end) {
    return !((start < 0) || (start >= g.order) || (end < 0) || (end >= g.order));
}

void addEdge(graph *g, int start, int end) {
    if(!checkBounds(*g, start, end))
        return;
    addToList(&g->vertices[start], end);
}

bool isEdge(graph g, int start, int end) {
    if(!checkBounds(g, start, end))
        return false;
    
    return searchForNode(g.vertices[start], end);
}

void printGraph(graph g) {
    for(int i = 0; i < g.order; ++i) {
        printf(" [%3d] ::  ", i);
        node *temp = g.vertices[i].head;
        while(temp) {
            printf("%3d, ", temp->val);
            temp = temp -> next;
        }
        printf("\b\b  \n");
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

        addEdge(&g, start, end);
    }

    traverseGraph(g, 0, 0, NULL);
    freeGraph(&g);
    return 0;
}