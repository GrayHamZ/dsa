#ifndef TYPES_H
#define TYPES_H

// Define a maximum length for the key
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Deletes a node with the given key from the BST.
 * @param root The current root of the BST.
 * @param key_data The string key to delete.
 * @return BST The new root of the BST after deletion.
 */
BST deleteNode(BST root, const char *key_data) {
    // TODO...
    if (root == NULL){
      printf("Key \"%s\" not found for deletion.\n", key_data);
      return NULL;
    }
        

    int cmp = strcmp(key_data, root->key);

    if (cmp < 0) {
        root->LC = deleteNode(root->LC, key_data);
    }
    else if (cmp > 0) {
        root->RC = deleteNode(root->RC, key_data);
    }
    else {
        // FOUND NODE TO DELETE
        if (root->LC == NULL && root->RC == NULL) {
            // CASE 1: Leaf
            free(root->key);
            free(root);
            return NULL;
        }
        else if (root->LC == NULL) {
            // CASE 2: Only right child
            BST temp = root->RC;
            free(root->key);
            free(root);
            return temp;
        }
        else if (root->RC == NULL) {
            // CASE 2: Only left child
            BST temp = root->LC;
            free(root->key);
            free(root);
            return temp;
        }
        else {
            // CASE 3: Two children
            BST succ = root->RC;
            while (succ->LC != NULL)
                succ = succ->LC;
            // SAFE KEY REPLACEMENT (FIXED)
            free(root->key);
            root->key = malloc(strlen(succ->key) + 1);
            strcpy(root->key, succ->key);

            // Delete successor node
            root->RC = deleteNode(root->RC, succ->key);
        }
    }

    return root;
}

void inorderTraversal() {

}

void destroyTree () {

}

void insert () {
    
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Building BST for Deletion Test ---\n");
    // Keys: Apple, Banana, Grape, Kiwi, Mango(ROOT), Orange, Pineapple
    insert(&myTree, "Mango");      // Root
    insert(&myTree, "Apple");      // Left of Mango
    insert(&myTree, "Pineapple");  // Right of Mango
    insert(&myTree, "Banana");     // Right of Apple
    insert(&myTree, "Grape");      // Left of Pineapple
    insert(&myTree, "Orange");     // Right of Grape
    insert(&myTree, "Kiwi");       // Left of Orange

    printf("\nInitial In-Order Traversal:\n   ");
    inorderTraversal(myTree);
    printf("\n");

    // --- Deletion Tests ---

    printf("\n--- Test 1: Delete Leaf Node (Kiwi) ---\n");
    // Kiwi is a leaf node (0 children)
    myTree = deleteNode(myTree, "Kiwi");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 2: Delete Node with 1 Child (Apple) ---\n");
    // Apple has 1 child (Banana)
    myTree = deleteNode(myTree, "Apple");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 3: Delete Node with 2 Children (Mango - the Root) ---\n");
    // Mango is replaced by its successor (Orange)
    myTree = deleteNode(myTree, "Mango");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 4: Delete Non-Existent Key (Zebra) ---\n");
    myTree = deleteNode(myTree, "Zebra");
    printf("No change expected: ");
    inorderTraversal(myTree);
    printf("\n");

    // 2. Clean up memory
    destroyTree(myTree);
    printf("\nTree destroyed and memory freed.\n");

    return 0;
}