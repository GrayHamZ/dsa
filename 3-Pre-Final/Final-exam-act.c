#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum length for the key
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;


void insert(BST *tree, const char *key_data) {
    // TODO...
    BST toInsert = (BST)malloc(sizeof(struct node));
    // ALLOCATE MEMORY FOR THE char *key 
    toInsert->key = (char *)malloc(sizeof(char) * (strlen(key_data) + 1)); // +1 for null terminator

    if (toInsert != NULL) {
        strcpy(toInsert->key, key_data);
        printf("%s\n", toInsert->key);
        printf("\n");
        toInsert->LC = NULL;
        toInsert->RC = NULL;

        BST *trav;
        // stops loop if NULL or is the identical,
        for (trav = tree; *trav != NULL && strcmp((*trav)->key, key_data) != 0; trav = strcmp(key_data, (*trav)->key) > 0 ? &(*trav)->RC : &(*trav)->LC) {}

        if (*trav == NULL) {
            *trav = toInsert;
        } else {
            free(toInsert);
            return;
        }
    }
}

void inorderTraversal(BST tree) {
    // TODO...
    if (tree != NULL) {
        inorderTraversal(tree->LC);
        printf("%s ", tree->key);
        inorderTraversal(tree->RC);
    }
}

void preorderTraversal(BST tree) {
    // TODO...
    if (tree != NULL) {
        printf("%s ", tree->key);
        preorderTraversal(tree->LC);
        preorderTraversal(tree->RC);
    }
}

void postorderTraversal(BST tree) {
    // TODO...
    if (tree != NULL) {
        postorderTraversal(tree->LC);
        postorderTraversal(tree->RC);
        printf("%s ", tree->key);
    }
}

/**
 * @brief Frees all memory allocated for the BST nodes, including the string keys.
 * * @param tree The root of the tree to destroy.
 */
void destroyTree(BST tree) {
    // DESTROY TREE IS BASICALLY POST ORDER BUT FREE THE TREE AT THE END
    if (tree != NULL) {
        destroyTree(tree->LC);
        destroyTree(tree->RC);

        if (tree->key != NULL) {
            free(tree->key);
        }

        free(tree);
    }
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Initializing and Inserting String Data into BST ---\n");

    // Root: 'Mango'
    // Left: 'Apple', 'Banana'
    // Right: 'Pineapple', 'Grape', 'Orange', 'Kiwi'
    insert(&myTree, "Mango");
    insert(&myTree, "Apple");
    insert(&myTree, "Pineapple");
    insert(&myTree, "Banana");
    insert(&myTree, "Grape");
    insert(&myTree, "Orange");
    insert(&myTree, "Kiwi");

    // Test duplicate handling
    insert(&myTree, "Mango");

    printf("\n\n--- BST Traversal Results ---\n");

    // In-Order: Sorted (Apple, Banana, Grape, Kiwi, Mango, Orange, Pineapple)
    printf("1. In-Order Traversal (Left-Root-Right, Sorted):\n");
    printf("   ");
    inorderTraversal(myTree);
    printf("\n\n");

    // Pre-Order: Root first (Mango, Apple, Banana, Grape, Kiwi, Pineapple, Orange)
    printf("2. Pre-Order Traversal (Root-Left-Right):\n");
    printf("   ");
    preorderTraversal(myTree);
    printf("\n\n");

    // Post-Order: Root last (Kiwi, Grape, Banana, Apple, Orange, Pineapple, Mango)
    printf("3. Post-Order Traversal (Left-Right-Root):\n");
    printf("   ");
    postorderTraversal(myTree);
    printf("\n\n");

    // 3. Clean up memory
    destroyTree(myTree);
    printf("Tree destroyed and memory freed.\n");

    return 0;
}