#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int **arr;
    int degree;
} dualPoly;

dualPoly *createPolynomialPair(int degree) {
    dualPoly *ret = (dualPoly *) malloc(sizeof(dualPoly));
    ret->degree = degree;
    ret->arr = (int **) malloc(sizeof(int *) * 2);
    ret->arr[0] = (int *) calloc(degree * 2 + degree * degree, sizeof(int));
    ret->arr[1] = (int *) calloc(degree * 2 + degree * degree, sizeof(int));
    return ret;
}

void freeDualPoly(dualPoly *d) {
    d->degree = 0;
    for(int i = 0; i < 2; ++i)
        free(d->arr[i]);
    free(d->arr); 
}

void clearPolyC(dualPoly *a) {
    for(int i = 0; i < a->degree * a->degree; ++i) {
        a->arr[0][i + a->degree * 2] = 0;
        a->arr[1][i + a->degree * 2] = 0;
    }
}

void printAllPoly(dualPoly p) {
    printf("Polynomial A:   ");
    for(int i = 0; i < p.degree; ++i) {
        if(p.arr[0][i] == 0 && p.arr[1][i] == 0)
            continue;
        printf("(%d)x^%d + ", p.arr[0][i], p.arr[1][i]);
    }
    printf("\b\b\b   \n");
    printf("Polynomial B:   ");
    for(int i = 0; i < p.degree; ++i) {
        if(p.arr[0][i + p.degree] == 0 && p.arr[1][i + p.degree] == 0)
            continue;
        printf("(%d)x^%d + ", p.arr[0][i + p.degree], p.arr[1][i + p.degree]);
    }
    printf("\b\b\b   \n");
    printf("Polynomial C:   ");
    for(int i = 0; i < p.degree * p.degree; ++i) {
        if(p.arr[0][i + p.degree * 2] == 0 && p.arr[1][i + p.degree * 2] == 0)
            continue;
        printf("(%d)x^%d + ", p.arr[0][i + p.degree * 2], p.arr[1][i + p.degree * 2]);
    }
    printf("\b\b\b   \n");
}

//Offset -> 1 : A, 2 : B, 3 : C
void inputPoly(dualPoly *p, int offset) {
    int o = (offset - 1) * p->degree;
    printf("Enter %d pairs of coefficient and power\n Make sure that the pairs are in ascending order of power\n", p->degree);
    for(int i = 0; i < p->degree; ++i) {
        printf("Pair %d of %d: ", i + 1, p->degree);
        scanf("%d %d", &p->arr[0][i + o], &p->arr[1][i + o]);
    }
}

void printPoly(dualPoly *p, int offset) {
    int o = (offset - 1) * p->degree;

    char poly;
    switch(offset) {
        case 1: poly = 'A'; break;
        case 2: poly = 'B'; break;
        case 3: poly = 'C'; break;
    }

    printf("Polynomial %c:   ", poly);
    for(int i = 0; i < offset != 3 ? p->degree : p->degree * p->degree; ++i) {
        if(p->arr[0][i + o] == 0 && p->arr[1][i + o] == 0)
            continue;
        printf("(%d)x^%d + ", p->arr[0][i + o], p->arr[1][i + o]);
    }
    printf("\b\b\b   \n");
}

void addPoly(dualPoly *a) {
    int ptrA = 0, ptrB = a->degree, ptrC = a->degree * 2;
    while(ptrA < a->degree && ptrB < (a->degree*2 - 1)) {
        if(a->arr[1][ptrA] > a->arr[1][ptrB]) {
            printf("A: %d %d\n", a->arr[0][ptrA], a->arr[1][ptrA]);
            a->arr[0][ptrC] = a->arr[0][ptrA];
            a->arr[1][ptrC] = a->arr[1][ptrA];
            ptrA++; ptrC++;
        } else if (a->arr[1][ptrA] < a->arr[1][ptrB]) {
            printf("B: %d %d\n", a->arr[0][ptrB], a->arr[1][ptrB]);
            a->arr[0][ptrC] = a->arr[0][ptrB];
            a->arr[1][ptrC] = a->arr[1][ptrB];
            ptrB++; ptrC++;
        } else {
            printf("C: %d %d %d %d\n", a->arr[0][ptrA], a->arr[1][ptrA], a->arr[0][ptrB], a->arr[1][ptrB]);
            a->arr[0][ptrC] = a->arr[0][ptrA] + a->arr[0][ptrB];
            a->arr[1][ptrC] = a->arr[1][ptrB];
            ptrA++; ptrB++; ptrC++;
        }
    }

    while(ptrA < a->degree) {
        a->arr[0][ptrC] = a->arr[0][ptrA];
        a->arr[1][ptrC] = a->arr[1][ptrA];
        ptrA++; ptrC++;
    }

    while(ptrB < (a->degree*2 - 1)) {
        a->arr[0][ptrC] = a->arr[0][ptrB];
        a->arr[1][ptrC] = a->arr[1][ptrB];
        ptrB++; ptrC++;
    }
}

void subPoly(dualPoly *a) {
    int ptrA = 0, ptrB = a->degree, ptrC = a->degree * 2;
    while(ptrA < a->degree && ptrB < (a->degree*2 - 1)) {
        if(a->arr[1][ptrA] > a->arr[1][ptrB]) {
            printf("A: %d %d\n", a->arr[0][ptrA], a->arr[1][ptrA]);
            a->arr[0][ptrC] = a->arr[0][ptrA];
            a->arr[1][ptrC] = a->arr[1][ptrA];
            ptrA++; ptrC++;
        } else if (a->arr[1][ptrA] < a->arr[1][ptrB]) {
            printf("B: %d %d\n", a->arr[0][ptrB], a->arr[1][ptrB]);
            a->arr[0][ptrC] = -a->arr[0][ptrB];
            a->arr[1][ptrC] = a->arr[1][ptrB];
            ptrB++; ptrC++;
        } else {
            printf("C: %d %d %d %d\n", a->arr[0][ptrA], a->arr[1][ptrA], a->arr[0][ptrB], a->arr[1][ptrB]);
            a->arr[0][ptrC] = a->arr[0][ptrA] - a->arr[0][ptrB];
            a->arr[1][ptrC] = a->arr[1][ptrB];
            ptrA++; ptrB++; ptrC++;
        }
    }

    while(ptrA < a->degree) {
        a->arr[0][ptrC] = a->arr[0][ptrA];
        a->arr[1][ptrC] = a->arr[1][ptrA];
        ptrA++; ptrC++;
    }

    while(ptrB < (a->degree*2 - 1)) {
        a->arr[0][ptrC] = -a->arr[0][ptrB];
        a->arr[1][ptrC] = -a->arr[1][ptrB];
        ptrB++; ptrC++;
    }
}

void diffPoly(dualPoly *a) {
    for(int i = 0; i < a->degree; ++i) {
        int coef = a->arr[0][i];
        int power = a->arr[1][i];
        int dcoef = coef * power;
        int dpower = dpower - 1;

        a->arr[0][a->degree * 2 + i] = dcoef;
        a->arr[1][a->degree * 2 + i] = power;
    }
}

int _firstZeroInPolyC(dualPoly *p) {
    printf("FINDING ZERO\n");
    int o = 2 * p->degree;
    for(int i = 0; i < p->degree * p->degree; ++i) {
        if(p->arr[0][i + o] == 0 && p->arr[1][i+o] == 0)
            return i + o;
    }
    return 2*p->degree + p->degree * p->degree;
}

void _addInPositionPolyC(dualPoly *p, int pow, int val) {
    int o = 2 * p->degree;
    //perform bin search;
    int start = p->degree * 2;
    int end = _firstZeroInPolyC(p) - 1;
    int mid = (start + end)/2;
    while(start <= end) {
        mid = (start + end) / 2;

        int powerMid = p->arr[1][mid];
        if(pow > powerMid)  //In descending order
            end = mid - 1;
        else if(pow < powerMid)
            start = mid + 1;
        else
            break;
    }
    if(p->arr[1][mid] == pow) {
        p->arr[0][mid] += val;
    } else {
        int pos = _firstZeroInPolyC(p);
        p->arr[0][pos] = val;
        p->arr[1][pos] = pow;
    }
}

void multPoly(dualPoly *a) {
    for(int i = 0; i < a->degree; ++i) {
        for(int j = 0; j < a->degree; ++j) {
            int coef = a->arr[0][i] * a->arr[0][j + a->degree];
            int pow  = a->arr[1][i] + a->arr[1][j + a->degree];
            _addInPositionPolyC(a, pow, coef);
        }
    }
}

int main() {
    dualPoly *a = createPolynomialPair(3);
    inputPoly(a, 1);
    inputPoly(a, 2);
    multPoly(a);
    printAllPoly(*a);
}