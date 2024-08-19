#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int max(int a, int b) {
    return a > b ? a: b;
}

struct node {
    double         val;
    struct node   *left;
    struct node   *right;
    int            h;
};

typedef struct node node;



node *makeNode(int val) {
    node *n  = (node *) malloc(sizeof(node));
    n->val   = val;
    n->left  = NULL;
    n->right = NULL;
    n->h     = 0;
    return n;
}

int height(node *t){
    if(t == NULL)
        return 0;
    if(t->left == NULL && t->right == NULL)
        return 1;
    return 1 + max(height(t->left), height(t->right));
}

node *rotateLeft(node *n) {
    node *nr = n->right, *nrl = n->right->left;
    nr->left = n;
    n->right = nrl;

    nr->h = height(nr);
    n->h  = height(n);
    return nr;
}

node *rotateRight(node *n) {
    node *nl = n->left, *nlr = n->left->right;
    nl->right = n;
    n->left = nlr;

    nl->h = height(nl);
    n->h  = height(n);

    return nl;
}

node *insertNode(node *n, int val) {
    if(n == NULL)
        return makeNode(val);
    
    if(val < n->val) {
        n->left  = insertNode(n->left, val);
    } else if(val > n->val) {
        n->right = insertNode(n->right, val);
    } else
        return n;
    
    n->h = 1 + max(height(n->left), height(n->right));

    int balance = height(n->left) - height(n->right);

    //Left of Left
    if(balance > 1 && val < n->left->val) {
        return rotateRight(n);
    } 
    //Right of Left
    else if (balance > 1 && val > n->left->val) {
       n->left =  rotateLeft(n->left);
       return rotateRight(n);
    }
    //Left of Right
    else if (balance < -1 && val < n->right->val) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    //Right of Right
    else if (balance < -1 && val > n->right->val){
        return rotateLeft(n);
    }

    return n;
}

node *deleteNode(node *n, int key) {
    if(n == NULL) return NULL;
         if(key < n->val)  n->left = deleteNode(n->left , key);
    else if(key > n->val) n->right = deleteNode(n->right, key);
    else {
        if(n->left == NULL || n->right == NULL) {
            node *temp = n->left == NULL ? n->right: n->left;
            free(n);
            n = temp;       //Either n = NULL or n = left|right
        } else {
            node *temp = n->right;

            while(temp->left != NULL)
                temp = temp->left;

            n->val = temp->val;

            n->right = deleteNode(n->right, temp->val);
        }
    }

    if(n == NULL)
        return NULL;

    n->h = height(n);

    int bf = height(n->left)        - height(n->right),
        bfl= n->left ? height(n->left->left)  - height(n->left->right) : 0,
        bfr= n->right ? height(n->right->left) - height(n->right->right) : 0;

    if(bf > 1 && bfl >= 0)
        return rotateRight(n);

    if(bf > 1 && bfl < 0) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    if(bf < -1 && bfr <=0)
        return rotateLeft(n);
    
    if(bf < -1 && bfr > 0) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    
    return n;
}

void drawTree(node *n, int level, char c) {
    if(n == NULL) return;
    for(int i = 0; i < level - 1; ++i) printf("         ");
    if(level >= 1)
        printf("%s───────", c=='R' ? "└":"├");
    printf(" %.1lf %c\n", n->val, c);
    drawTree(n->left, level + 1, 'L');
    drawTree(n->right, level + 1, 'R');
}

int main() {
    node *tree;

    tree = insertNode(tree, 9);
    tree = insertNode(tree, 5);
    tree = insertNode(tree, 10);
    tree = insertNode(tree, 0);
    tree = insertNode(tree, 6);
    tree = insertNode(tree, 11);
    tree = insertNode(tree, -1);
    tree = insertNode(tree, 1);
    tree = insertNode(tree, 2);

    drawTree(tree, 0, '=');
    tree = deleteNode(tree, 0);
    drawTree(tree, 0, '0');
}