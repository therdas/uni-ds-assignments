#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


struct node{
    int pow;
    double coef;
    struct node *next;
} ;
typedef struct node node;


node *createNode(double coef, int pow) {
    node *r = (node *)malloc(sizeof(node));
    r->pow = pow;
    r->coef = coef;
    r->next = NULL;
    return r;
}

typedef struct {
    node *head;
    node *tail;
} poly;

poly *createPoly() {
    poly *r = (poly *) malloc(sizeof(poly));
    r->head = NULL;
    r->tail = NULL;
    return r; 
}

void freePoly(poly *p) {
    while(p->head) {
        node *temp = p->head->next;
        free(p->head);
        p->head = temp;
    }
    p->head = NULL;
    p->tail = NULL;
}

void appendTerm(poly *p, double coef, int pow) {
    node *temp = createNode(coef, pow);
    if(p->head == NULL && p->tail == NULL) {
        p->head = temp;
        p->tail = temp;
    } else {
        p->tail->next = temp;
        p->tail = temp;
    }
}

void inputPoly(poly *a) {
    printf("Enter the number of terms: ");
    int n;
    scanf("%d", &n);
    printf("Enter the coeffecient power pairs (coef pow)(eg. 2x^5 is input as >> 2 5): \n");
    for(int i = 0; i < n; ++i) {
        int pow; 
        double coef;
        scanf("%lf %d", &coef, &pow);
        appendTerm(a, coef, pow);
    }
}

void printPoly(poly *p) {
    node *t = p->head;
    while(t){
        if(t->pow == 0)
            printf("(%.2lf) + ", t->coef);
        else
            printf("(%.2lf)x^%d + ", t->coef, t->pow);
        t = t->next;
    }
    printf("\b\b\b   \n");
}

poly *addPoly(poly *a, poly *b) {
    poly *c = createPoly();

    node *ptrA = a->head, *ptrB = b->head;
    while(ptrA != NULL && ptrB != NULL) {
        if(ptrA->pow > ptrB->pow) {
            appendTerm(c, ptrA->coef, ptrA->pow);
            ptrA = ptrA->next;
        } else if(ptrA -> pow < ptrB->pow) {
            appendTerm(c, ptrB->coef, ptrB->pow);
            ptrB = ptrB->next;
        } else {
            appendTerm(c, ptrA->coef + ptrB->coef, ptrA->pow);
            ptrA = ptrA->next; ptrB = ptrB->next;
        }
    }

    while(ptrA) {
        appendTerm(c, ptrA->coef, ptrA->pow);
        ptrA = ptrA->next;
    }

    while(ptrB) {
        appendTerm(c, ptrB->coef, ptrB->pow);
        ptrB = ptrB->next;
    }

    return c;
}

poly *subPoly(poly *a, poly *b) {
    poly *c = createPoly();

    node *ptrA = a->head, *ptrB = b->head;
    while(ptrA != NULL && ptrB != NULL) {
        if(ptrA->pow > ptrB->pow) {
            appendTerm(c, ptrA->coef, ptrA->pow);
            ptrA = ptrA->next;
        } else if(ptrA -> pow < ptrB->pow) {
            appendTerm(c, (-1) * ptrB->coef, ptrB->pow);
            ptrB = ptrB->next;
        } else {
            appendTerm(c, ptrA->coef - ptrB->coef, ptrA->pow);
            ptrA = ptrA->next; ptrB = ptrB->next;
        }
    }

    while(ptrA) {
        appendTerm(c, ptrA->coef, ptrA->pow);
        ptrA = ptrA->next;
    }

    while(ptrB) {
        appendTerm(c, (-1) * ptrB->coef, ptrB->pow);
        ptrB = ptrB->next;
    }

    return c;
}

poly *diffPoly(poly *a) {
    poly *c = createPoly();
    node *ptrA = a->head;
    while(ptrA) {
        appendTerm(c, ptrA->coef * ptrA->pow, ptrA->pow - 1);
    }
    return c;
}

void insertInPosition(poly *a, double coef, int pow) {
    node *t = a->head, *p = NULL;
    while(t != NULL && t->pow > pow){
        p = t;
        t = t->next; 
    }
    if(t != NULL && t->pow == pow) {
        t->coef += coef;
    } else if(!p) {
        a->head = createNode(coef, pow);
        a->head->next = t;
    } else {
        p->next = createNode(coef, pow);
        p->next->next = t;
    }
}

poly *multPoly(poly *a, poly *b) {
    poly *c = createPoly();
    node *ptrA = a->head;
    while(ptrA) {
        node *ptrB = b->head;
        while(ptrB) {
            insertInPosition(c, ptrA->coef * ptrB->coef, ptrA->pow + ptrB->pow);
            ptrB = ptrB->next;
        }
        ptrA = ptrA -> next;
    }
    return c;
}

int main() {
    poly *a = createPoly(), *b = createPoly(), *c;
    inputPoly(a);
    inputPoly(b);
    c = multPoly(a, b);
    printf("   "); printPoly(a);
    printf(" + "); printPoly(b);
    printf(" = "); printPoly(c);
}