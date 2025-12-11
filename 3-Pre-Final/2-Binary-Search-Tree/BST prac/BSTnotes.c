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
    if (toInsert != NULL) {
        toInsert->data = data;
        toInsert->right = NULL;
        toInsert->left = NULL;

        Tree *trav;
        trav = T; // Assuming typedef *Tree: 
        // if your parameter is Tree *T , then you just use T
        // if its Tree T then do &T

        // the loop stops if *trav is null or if trav's data is equal to data
        // increment: check if the data is greater than trav->data, if so go right else left
        for (trav = T; *trav != NULL && (*trav)->data != data; trav = data > (*trav)->data ? &(*trav)->right : &(*trav)->left) {}

        if (*trav == NULL) {
            *trav = toInsert;
        }
    }
}

void insertRecursion(Tree *T, int data) {

}

bool isFound(Tree T, int x) {
    Tree *trav;
    for (trav = &T; (*trav) != NULL && (*trav)->data != x; trav = x > (*trav)->data ? &(*trav)->right : &(*trav)->left) {}

    return (*trav) == NULL ? false : true;
}

bool isFoundRecursion(Tree T, int x) {

}

void deleteElem(Tree *T, int x) {
    Tree *trav;
    Tree temp;

    // WE NEED TO FIND THE ELEMENT FIRST
    for (trav = T; (*trav) != NULL && (*trav)->data != x; trav = x > (*trav)->data ? &(*trav)->right : &(*trav)->left) {}

    if (*trav != NULL) {
        // check if the right child exists, if null then just make *trav = to that node
        if ((*trav)->right == NULL) {
            temp = *trav;
            *trav = temp->left;
        } else {
            // Find the minimum number on the right side, so we want to be on the right
            Tree *successor = &(*trav)->right;

            // We then want to travers only left children to find the minimum
            while ((*successor)->left != NULL) { // ->left because we want to stop at that last left node not null
                successor = &(*successor)->left; // keep going
            }

            // Now that we have the minimum we want to assign the minimum data to the data you want to delete
            (*trav)->data = (*successor)->data;
            // Okay now we want to make the successor the right node incase if its an innode
            // Note: the reason why we take the right is because there should be no left side since
            // we are technically the minimum it wouldnt make sense. Right side could either be null or a node
            
            temp = *successor;
            *successor = (*successor)->right; // successor is null then it ends at its parent else it replaces it with a different node
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