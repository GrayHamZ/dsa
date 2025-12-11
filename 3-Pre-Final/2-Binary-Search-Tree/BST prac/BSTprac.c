#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} *Tree;

void initTree(Tree *T);
void populateTree(Tree *T, int arr[], int size);
void insertTree(Tree *T, int data);
void insertRecursion(Tree *T, int data);
bool isFound(Tree T, int x);
bool isFoundRecursion(Tree T, int x);
void deleteElem(Tree *T, int x);
void preOrder(Tree T);

int main() {
    Tree T;
	int arr[] = {10, 5, 7, 14, 12, 18, 11, 15};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    int x = 14;
    printf("LOOP: %d %s in the tree\n", x, isFound(T, x) ? "IS" : "IS NOT");

    x = 14;
    printf("RECURSION: %d %s in the tree\n", x, isFound(T, x) ? "IS" : "IS NOT");

    x = 14;
    printf("\nBefore deleting %d: (Pre-order traversal)\n", x);
    preOrder(T);

    deleteElem(&T, x);

    printf("\nAfter deleting %d: (Pre-order traversal)\n", x);
    preOrder(T);

    return 0;
}

void initTree(Tree *T) {
    *T = NULL;
}

void populateTree(Tree *T, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        insertTree(T, arr[i]);
    }
}

void insertTree(Tree *T, int data) {
    Tree toInsert = (Tree)malloc(sizeof(struct node));
    Tree *trav;

    for (trav = T; *trav != NULL && (*trav)->data != data; trav = data > (*trav)->data ? &(*trav)->right : &(*trav)->left) {}

    if (*trav == NULL) {
        toInsert->data = data;
        toInsert->left = NULL;
        toInsert->right = NULL;

        *trav = toInsert;
    } else {
        free(toInsert);
    }
}

void insertRecursion(Tree *T, int data) {

}

bool isFound(Tree T, int x) {

}

bool isFoundRecursion(Tree T, int x) {

}

void deleteElem(Tree *T, int x) {
    Tree *trav;
    Tree temp;
    for (trav = T; *trav != NULL && (*trav)->data != x; trav = x > (*trav)->data ? &(*trav)->right : &(*trav)->left) {}

    if (*trav != NULL) {
        if ((*trav)->right == NULL) {
            temp = *trav;
            *trav = (*trav)->left;
        } else {
            Tree *successor = &(*trav)->right;
            while ((*successor)->left != NULL) {
                successor = &(*successor)->left;
            }
            (*trav)->data = (*successor)->data;
            
            temp = *successor;
            *successor = (*successor)->right;
        }
        free(temp);
    }
}

void preOrder(Tree T) {
    if (T != NULL) {
        printf("%d ", T->data);
        preOrder(T->left);
        preOrder(T->right);
    } else {
        printf("_ ");
    }
}