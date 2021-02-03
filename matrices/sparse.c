#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

static const int HEADER = 0;
static const int ROWS = 0;
static const int COLS = 1;
static const int ELEMENTS = 2;
static const int ROW = 0;
static const int COL = 1;
static const int VAL = 2;

void swap(int *x, int *y) {
    if(x == y)
        return;

    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

int max(int i, int j){
    return i > j ? i : j;
}

typedef struct {
    int **matrix;
    int top;
} sparseMatrix;

sparseMatrix *SparseMatrix(int rows, int cols, int elements){
    sparseMatrix *r = (sparseMatrix *) malloc(sizeof(sparseMatrix));
    
    // elements # of rows with 1 extra for header
    r->matrix = (int **) malloc(sizeof(int *) * (elements + 1));

    // each row has 3 columns
    for(int i = 0; i <= elements; ++i)
        r->matrix[i] = (int *) calloc(3, sizeof(int));

    r->matrix[HEADER][ROWS] = rows;
    r->matrix[HEADER][COLS] = cols;
    r->matrix[HEADER][ELEMENTS] = elements;

    r->top = 0;

    return r;
}

void insert(sparseMatrix *m, int row, int col, int elem) {
    if(m->top == m->matrix[HEADER][ELEMENTS])
        return;

    m->matrix[++(m->top)][ROW] = row;
    m->matrix[   m->top ][COL] = col;
    m->matrix[   m->top ][VAL] = elem;

    printf("INSERTED AT %d", m->top);
}

void swapLine(sparseMatrix *m, int i, int j) {
    swap(&m->matrix[i][ROW], &m->matrix[j][ROW]);
    swap(&m->matrix[i][COL], &m->matrix[j][COL]);
    swap(&m->matrix[i][VAL], &m->matrix[j][VAL]);
}

void sortMatrix(sparseMatrix *m) {
    int size = m->matrix[HEADER][ELEMENTS];
    
    //Sort acc to COLS
    for(int i = 1; i <= size; ++i)
        for(int j = 1; j <= size - i; ++j)
            if(m->matrix[j][COL] > m->matrix[j+1][COL])
                swapLine(m, j, j+1);

    //Sort acc to ROWS
    for(int i = 1; i <= size; ++i)
        for(int j = 1; j <= size - i; ++j)
            if(m->matrix[j][ROW] > m->matrix[j+1][ROW])
                swapLine(m, j, j+1);
}

void transpose(sparseMatrix *m) {
    for(int i = 1; i <= m->matrix[HEADER][ELEMENTS]; ++i)
        swap(&m->matrix[i][ROW], &m->matrix[i][COL]);
    
    sortMatrix(m);
}

void printRepresentation(sparseMatrix *m) {

    printf("+--------------------+\n");
    for(int j = 0; j < 3; ++j) {
        printf("| %4d ", m->matrix[0][j]);
    }
    printf("|\n+--------------------+\n");

    for(int i = 1; i <= m->matrix[HEADER][ELEMENTS]; ++i) {
        for(int j = 0; j < 3; ++j) {
            printf("| %4d ", m->matrix[i][j]);
        }
        printf("|\n");
    }
    printf("+--------------------+\n");
}

int main() {
    int m, n, elements;
    printf("Enter the dimension of the matrix (m n): ");
    scanf("%d %d", &m, &n);
    printf("Enter the number of elements: ");
    scanf("%d", &elements);

    sparseMatrix *mat = SparseMatrix(m, n, elements);
    for(int i = 0; i < elements; ++i) {
        printf("Enter the row and column of the [%d]th element, followed by the element (row col val): ", i + 1);
        int r, c, elem;
        scanf("%d %d %d", &r, &c, &elem);
        insert(mat, r, c, elem);
    }
    printf("\n\nOriginal representation of the matrix is: \n");
    printRepresentation(mat);
    transpose(mat);
    printf("\n\nTransposed representation of the matrix is: \n");
    printRepresentation(mat);

}