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
    insert(D, 2);
    insert(D, 3);
    insert(D, 4);
    insert(D, 21);
    insert(D, 21);
    insert(D, 41);
    insert(D, 31);
    insert(D, 11);
    insert(D, 11);
    insert(D, 1);
    delete(D, 11);

    printDict(D);

    return 0;
}

void insert(Dictionary D, int data) {
    Nodetype newNode = (Nodetype)malloc(sizeof(struct node));
    newNode->data = data;
    int hashIdx = hash(data);

    Nodetype *trav;

    // LOGIC: So the loop only runs if *trav is not NULL 
    // or if the data in trav is less than the data to be inserted
    for (trav = &D[hashIdx] ; *trav != NULL && (*trav)->data < data; trav = &(*trav)->next ) {}
    // Possible outputs: *trav == NULL, (*trav)->data >= data

    // Checks if *trav == NULL first so (*trav)->data wont dereference a NULL pointer
    if (*trav == NULL || (*trav)->data != data) {
        newNode->next = *trav;
        (*trav) = newNode;
    }        

}

void delete(Dictionary D, int data) {
    int hashIdx = hash(data);

    Nodetype *trav;
    for (trav = &D[hashIdx]; *trav != NULL && (*trav)->data != data; trav = &(*trav)->next) {}
    // possible outputs: *trav == NULL or (*trav)->data == data

    // we only need to delete if its not null and trav is equal to data
    if (*trav != NULL && (*trav)->data == data) {
        Nodetype temp = *trav;
        *trav = temp->next;
        free(temp);
    }
}

void printDict(Dictionary D) {
    int i;
    for (i = 0; i < MAX; i++) {
        Nodetype trav;
        printf("[%d]:",i);
        for (trav = D[i]; trav != NULL; trav = trav->next) {
            printf("%d->", trav->data);
        }
        printf("\n");
    }
}

void initDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        D[i] = NULL;
    }
}

int hash(int data) {
    return data % MAX;
}
