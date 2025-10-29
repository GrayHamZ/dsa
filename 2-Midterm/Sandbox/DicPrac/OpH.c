#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 10

typedef struct node {
    int data;
    struct node *next;
} *Nodetype;

typedef Nodetype Dictionary[MAX];

// dictionary functions
void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
bool inDict(Dictionary D, int data);
void delete(Dictionary D, int data);
void printDict(Dictionary D);

int main() {
    Dictionary D;

    initDict(D);

    insert(D, 1);
    insert(D, 2);
    insert(D, 22);
    insert(D, 12);
    delete(D, 22);

    if (inDict(D, 22)) {
        printf("IN\n");
    }

    printDict(D);
}

void printDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: ", i);

        Nodetype trav = D[i];
        for ( ; trav != NULL ; trav = trav->next ) {
            printf("%d-> ", trav->data);
        }

        printf("\n");
    }
}

bool inDict(Dictionary D, int data) {
    int hashIdx = hash(data);

    Nodetype* trav = &D[hashIdx];

    for ( ; (*trav) != NULL && (*trav)->data != data ; trav = &(*trav)->next ) {}

    if ((*trav) != NULL) {
        return true;
    }    
    return false;
}

void delete(Dictionary D, int data) {
    int hashIdx = hash(data);

    Nodetype* trav = &D[hashIdx];

    for ( ; (*trav) != NULL && (*trav)->data != data ; trav = &(*trav)->next ) {}

    if ((*trav) != NULL) {
        Nodetype temp;
        temp = (*trav);
        (*trav) = temp->next;
    }
}

void insert(Dictionary D, int data) {
    Nodetype newNode = (Nodetype)malloc(sizeof(struct node));
    if (newNode == NULL) return;
    newNode->data = data;
    int hashIdx = hash(data);

    Nodetype* trav = &D[hashIdx];

    for ( ; (*trav) != NULL && (*trav)->data < data ; trav = &(*trav)->next ) {}

    if ((*trav) == NULL || (*trav)->data != data) {
        newNode->next = (*trav);
        (*trav) = newNode;
    } else {
        free(newNode);
    }
}

int hash(int data) {
    return data % MAX;
}

void initDict(Dictionary D) {
    for (int i = 0 ; i < MAX; i ++) {
        D[i] = NULL;
    }
}